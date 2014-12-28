#include "resources/SheetLoader.h"
#include "core/Constant.h"
#include "core/picojson.h"
#include "network/HttpClient.h"
#include <fstream>

USING_NS_CC;
using namespace network;

SheetLoader::SheetLoader()
{
}

SheetLoader::~SheetLoader()
{
}

bool SheetLoader::readFile(const std::string filename)
{
    std::string filePath = FileUtils::getInstance()->getWritablePath() + filename;
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
    ifstream ifs(fullPath.c_str());
    if (!ifs) return false;
    picojson::parse(this->jsonResult, ifs);
    return true;
}

void SheetLoader::downloadSheet(const std::string url, const std::string filename)
{
    this->status = DownloadStatus::DownloadBefore;
    HttpRequest* request = new HttpRequest();

    request->setUrl(url.c_str());
    CCLOG("downloadsheet1: %s", url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback([this, filename](HttpClient* client, HttpResponse* response) {
        CCLOG("setResponseClick");
        if (!response) {
            this->status = DownloadStatus::ResponseError;
            return;
        }
        
        if (0 != std::strlen(response->getHttpRequest()->getTag())) {
            CCLOG("%s completed", response->getHttpRequest()->getTag());
        }
        
        long statusCode = response->getResponseCode();
        auto statusString = StringUtils::format("HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
        CCLOG("response code: %ld", statusCode);
        
        if (!response->isSucceed()) {
            this->status = DownloadStatus::ResponseFailed;
            CCLOG("response failed");
            CCLOG("error buffer: %s", response->getErrorBuffer());
            return;
        }

        // ダウンロードしたデータをファイルに書き込む
        std::vector<char> *buffer = response->getResponseData();
        std::string filePath = FileUtils::getInstance()->getWritablePath() + filename;
        CCLOG("filepath: %s", filePath.c_str());
        
        std::ofstream ofs;
        ofs.open(filePath.c_str(), std::ios::out | std::ios::trunc);
        ofs.write(&(buffer->front()), buffer->size());
        ofs.flush();
        ofs.close();
        CCLOG("filepath: %s", (*buffer).data());

        this->status = DownloadStatus::DownloadSuccess;
    });
    
    request->setTag("SheetLoader::downloadSheet");
    HttpClient::getInstance()->send(request);
    request->release();
    this->status = DownloadStatus::SendRequest;
    CCLOG("downloadsheet2");
}
