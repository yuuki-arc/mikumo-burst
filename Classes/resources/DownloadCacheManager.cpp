#include "resources/DownloadCacheManager.h"
#include "core/Constant.h"
#include "core/picojson.h"
#include "network/HttpClient.h"
#include <fstream>

USING_NS_CC;
using namespace network;

DownloadCacheManager::DownloadCacheManager()
: loadStatus(LoadStatus::BeforeLoad)
{
}

DownloadCacheManager::~DownloadCacheManager()
{
}

bool DownloadCacheManager::init()
{
    loader = new JsonLoader();
    return true;
}

void DownloadCacheManager::setCallback(const std::function<void (Ref *)> &callback)
{
    this->callback = callback;
}

bool DownloadCacheManager::loadData()
{
    bool readFlg = loader->readFile(getFileName());
    if (readFlg)
    {
        this->loadStatus = LoadStatus::ReadSuccess;
    }
    else
    {
        if (!FileUtils::getInstance()->isFileExist(getFileName()))
        {
            // ファイルが存在しない場合はHttpRequest通信でダウンロード
            this->loadStatus = LoadStatus::DataDownload;
            loader->downloadData(getUrl(), getFileName());
        }
        else
        {
            this->loadStatus = LoadStatus::ReadError;
            CCLOG("file exists, but read error");
            return false;
        }
    }
    return true;
}

bool DownloadCacheManager::readData()
{
    if (loader == nullptr) return false;
    
    switch(this->loadStatus) {
        case LoadStatus::DataDownload:
        {
            // ダウンロード終了待ち
            if (loader->downloadStatus == JsonLoader::DownloadStatus::DownloadSuccess)
            {
                bool readFlg = loader->readFile(getFileName());
                if (readFlg)
                {
                    this->loadStatus = LoadStatus::ReadSuccess;
                }
                else
                {
                    this->loadStatus = LoadStatus::ReadError;
                    CCLOG("system error");
                    return false;
                }
            }
            break;
        }
        case LoadStatus::ReadSuccess:
        {
            this->loadStatus = LoadStatus::LoadComplete;
            if (callback) callback(this);
            break;
        }
        default:
            break;
    }
    return true;
}