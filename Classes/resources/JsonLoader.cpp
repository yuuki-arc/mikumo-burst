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

/**
 *  キャッシュファイルからデータを読み込む
 *
 *  @param filename ファイル名
 *  @return 正常終了はtrue、それ以外はfalse
 */
bool JsonLoader::readFile(const std::string filename)
{
    std::string filePath = FileUtils::getInstance()->getWritablePath() + filename;
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
    ifstream ifs(fullPath.c_str());
    if (!ifs) return false;
    picojson::parse(this->jsonResult, ifs);
    return true;
}

/**
 *  指定したURLから非同期でダウンロード処理を行う
 *  ダウンロードしたデータはメモリに保持する
 *
 *  @param url ダウンロード先URL
 *  @return 正常終了はtrue、それ以外はfalse
 */
void JsonLoader::downloadResponseData(const std::string url)
{
    this->downloadStatus = DownloadStatus::BeforeDownload;
    HttpRequest* request = new HttpRequest();

    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback([this](HttpClient* client, HttpResponse* response) {
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

        // レスポンスデータを保持する
        std::vector<char>* buffer = response->getResponseData();
        std::copy((*buffer).begin(), (*buffer).end(), back_inserter(responseData));

        this->downloadStatus = DownloadStatus::SaveResponseData;
    });
    
    request->setTag("JsonLoader::downloadData");
    HttpClient::getInstance()->send(request);
    request->release();
    this->downloadStatus = DownloadStatus::SendRequest;
}

/**
 *  レスポンスデータをキャッシュファイルに書き込む
 *  ファイルが存在する場合は上書きする
 *
 *  @param filename ファイル名
 *  @return 正常終了はtrue、それ以外はfalse
 */
void JsonLoader::writeCacheData(const std::string filename)
{
    this->downloadStatus = DownloadStatus::WritingCacheData;
    
    std::string filePath = FileUtils::getInstance()->getWritablePath() + filename;
    std::vector<char>* buffer = new std::vector<char>(responseData.begin(), responseData.end());
    std::ofstream ofs;
    ofs.open(filePath.c_str(), std::ios::out | std::ios::trunc);
    ofs.write(&(buffer->front()), buffer->size());
    ofs.flush();
    ofs.close();
    CCLOG("filepath: %s", (*buffer).data());
    
    this->downloadStatus = DownloadStatus::WritedCacheData;
}