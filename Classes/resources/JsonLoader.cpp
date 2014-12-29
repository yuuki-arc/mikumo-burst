#include "resources/JsonLoader.h"
#include "core/Constant.h"
#include "core/picojson.h"
#include "network/HttpClient.h"
#include <fstream>

USING_NS_CC;
using namespace network;

JsonLoader::JsonLoader()
: downloadStatus(DownloadStatus::BeforeDownload)
{
}

JsonLoader::~JsonLoader()
{
}

bool JsonLoader::readFile(const std::string filename)
{
    std::string filePath = FileUtils::getInstance()->getWritablePath() + filename;
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
    ifstream ifs(fullPath.c_str());
    if (!ifs) return false;
    picojson::parse(this->jsonResult, ifs);
    return true;
}

void JsonLoader::downloadData(const std::string url, const std::string filename)
{
    this->downloadStatus = DownloadStatus::BeforeDownload;
    HttpRequest* request = new HttpRequest();

    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback([this, filename](HttpClient* client, HttpResponse* response) {
        if (!response) {
            this->downloadStatus = DownloadStatus::ResponseError;
            return;
        }
        
        if (0 != std::strlen(response->getHttpRequest()->getTag())) {
            CCLOG("%s completed", response->getHttpRequest()->getTag());
        }
        
        long statusCode = response->getResponseCode();
        auto statusString = StringUtils::format("HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
        CCLOG("response code: %ld", statusCode);
        
        if (!response->isSucceed()) {
            this->downloadStatus = DownloadStatus::ResponseFailed;
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

        this->downloadStatus = DownloadStatus::DownloadSuccess;
    });
    
    request->setTag("JsonLoader::downloadData");
    HttpClient::getInstance()->send(request);
    request->release();
    this->downloadStatus = DownloadStatus::SendRequest;
}
