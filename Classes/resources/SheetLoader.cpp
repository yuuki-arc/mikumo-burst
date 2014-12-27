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

picojson::value SheetLoader::getSheet(const std::string filename)
{
    picojson::value v;
    std::string err;
    
    if (!FileUtils::getInstance()->isFileExist(filename))
    {
        // ファイルが存在しない場合はHttpRequest通信でダウンロード
        const std::string url = __GOOGLE_SHEET_URL;
        CCLOG("url = %s", url.c_str());
        downloadSheet(url, filename);
//        picojson::parse(v, response->getResponseData()->begin(), response->getResponseData()->end(), &err);
        CCLOG("download");
    }

    // ファイルから取得
    CCLOG("get file");
    std::string filePath = FileUtils::getInstance()->getWritablePath() + filename;
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
    CCLOG("fullpath = %s", fullPath.c_str());
    Data data = FileUtils::getInstance()->getDataFromFile(filename);
    ifstream ifs(fullPath.c_str());
    if (!ifs) return v;
    picojson::parse(v, ifs);
    
    return v;
}

bool SheetLoader::downloadSheet(const std::string url, const std::string filename)
{
    bool result = false;
    
    HttpRequest* request = new HttpRequest();
    // Google SpreadSheetの公開URL
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback([filename, &result](HttpClient* client, HttpResponse* response) {
        if (!response) {
            return;
        }
        
        if (0 != std::strlen(response->getHttpRequest()->getTag())) {
            CCLOG("%s completed", response->getHttpRequest()->getTag());
        }
        
        long statusCode = response->getResponseCode();
        auto statusString = StringUtils::format("HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
        CCLOG("response code: %ld", statusCode);
        
        if (!response->isSucceed()) {
            CCLOG("response failed");
            CCLOG("error buffer: %s", response->getErrorBuffer());
            return;
        }

        // ダウンロードしたデータを取り出す
        std::vector<char> *buffer = response->getResponseData();
        
        // ファイルパス作る
        std::string filePath = FileUtils::getInstance()->getWritablePath() + filename;
        
        // 書き込む
        std::ofstream ofs;
        ofs.open(filePath.c_str(), std::ios::out | std::ios::trunc);
        ofs.write(&(buffer->front()), buffer->size());
        ofs.flush();
        ofs.close();
        
        result = true;
    });
    request->setTag("SheetLoader::downloadSheet");
    HttpClient::getInstance()->send(request);
    request->release();
    
    return result;
}
