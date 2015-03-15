#include "resources/DownloadCacheManager.h"
#include "core/Constant.h"
#include "core/picojson.h"
#include <fstream>

USING_NS_CC;

DownloadCacheManager::DownloadCacheManager()
: loadStatus(LoadStatus::BeforeLoad)
, loader(nullptr)
{
}

DownloadCacheManager::~DownloadCacheManager()
{
}

/**
 *  初期化処理
 */
bool DownloadCacheManager::init()
{
    loader = new JsonLoader();
    return true;
}

/**
 *  コールバック関数をセットする
 *
 *  @param &callback コールバック関数
 */
void DownloadCacheManager::setCallback(const std::function<void (Ref *)> &callback)
{
    this->callback = callback;
}

/**
 *  アプリ情報がキャッシュファイルに存在するかチェックを行う
 *
 *  @return 存在する場合はtrue、存在しなければfalse
 */
bool DownloadCacheManager::isExistCacheFile()
{
    std::string filePath = FileUtils::getInstance()->getWritablePath() + getFileName();
    return FileUtils::getInstance()->isFileExist(filePath);
}

/**
 *  データを指定したURLから非同期でダウンロードしてメモリに保持する
 *
 *  @return 正常終了はtrue、それ以外はfalse
 */
bool DownloadCacheManager::downloadResponseData()
{
    this->loadStatus = LoadStatus::DataDownload;
    loader->downloadResponseData(getUrl());
    return true;
}

/**
 *  データを指定したURLから非同期でダウンロードしてキャッシュファイルに書き込む
 *
 *  @return 正常終了はtrue、それ以外はfalse
 */
bool DownloadCacheManager::downloadAndWriteCacheData()
{
    this->loadStatus = LoadStatus::DataDownload;
    loader->downloadResponseData(getUrl(), getFileName());
    return true;
}

/**
 *  キャッシュを読み込む
 *
 *  @return 正常終了はtrue、それ以外はfalse
 */
bool DownloadCacheManager::readCache()
{
    bool readFlg = loader->parseByFile(getFileName());
    return readFlg;
}

/**
 *  データをロードする
 *  ファイルキャッシュが存在する場合はキャッシュからファイル読み込みを行い、
 *  存在しない場合は指定したURLから非同期でダウンロードしてメモリに保持する
 *
 *  @return 正常終了はtrue、それ以外はfalse
 */
bool DownloadCacheManager::loadData()
{
    bool readFlg = loader->parseByFile(getFileName());
    if (readFlg)
    {
        // ファイル読み込み成功時はフラグ更新
        this->loadStatus = LoadStatus::ReadSuccess;
    }
    else
    {
        if (!isExistCacheFile())
        {
            // ファイルが存在しない場合はHttpRequest通信でダウンロード
            this->loadStatus = LoadStatus::DataDownload;
            loader->downloadResponseData(getUrl());
        }
        else
        {
            // 読み込み成功にもかかわらずファイルが存在しない場合はエラー処理
            this->loadStatus = LoadStatus::ReadError;
            CCLOG("file exists, but read error");
            return false;
        }
    }
    return true;
}

/**
 *  コールバック実行する
 *  データダウンロード中の場合はダウンロード完了を考慮して実行する
 *
 *  @return 正常終了はtrue、それ以外はfalse
 */
bool DownloadCacheManager::execCallback()
{
    if (loader == nullptr) return false;
    
    switch(this->loadStatus) {
        case LoadStatus::DataDownload:
        {
            // データダウンロード中時の処理
            if (loader->downloadStatus == JsonLoader::DownloadStatus::SaveResponseData)
            {
                // データダウンロード完了後の場合、メモリ読み込みを行う
                bool readFlg = loader->parseByJsonString();
                if (readFlg)
                {
                    // 読み込み成功したらフラグ更新
                    this->loadStatus = LoadStatus::ReadSuccess;
                }
                else
                {
                    // 読み込み失敗したらエラー処理
                    this->loadStatus = LoadStatus::ReadError;
                    CCLOG("system error");
                    return false;
                }
            }
            break;
        }
        case LoadStatus::ReadSuccess:
        {
            // 読み込み成功時の処理
            this->loadStatus = LoadStatus::LoadComplete;
            if (callback)
            {
                // コールバック関数がセットされていればコールバック実行する
                callback(this);
            }
            break;
        }
        default:
            break;
    }
    return true;
}

/**
 *  データを参照してコールバック実行する
 *  データダウンロード中の場合はダウンロード完了を考慮して実行する
 *
 *  @return 正常終了はtrue、それ以外はfalse
 */
bool DownloadCacheManager::execCallbackReferenceData()
{
    if (loader == nullptr) return false;
    
    switch(this->loadStatus) {
        case LoadStatus::DataDownload:
        {
            // データダウンロード中時の処理
            if (loader->downloadStatus == JsonLoader::DownloadStatus::SaveResponseData)
            {
                // ダウンロード成功（レスポンスデータ保存後）の場合、キャッシュに書き込む
                loader->writeCacheData(getFileName());
            }
            else if (loader->downloadStatus == JsonLoader::DownloadStatus::WritedCacheData)
            {
                // キャッシュ書き込み成功後の場合、ファイル読み込みを行う
                bool readFlg = loader->parseByFile(getFileName());
                if (readFlg)
                {
                    // 読み込み成功したらフラグ更新
                    this->loadStatus = LoadStatus::ReadSuccess;
                }
                else
                {
                    // 読み込み失敗したらエラー処理
                    this->loadStatus = LoadStatus::ReadError;
                    CCLOG("system error");
                    return false;
                }
            }
            break;
        }
        case LoadStatus::ReadSuccess:
        {
            // 読み込み成功時の処理
            this->loadStatus = LoadStatus::LoadComplete;
            if (callback)
            {
                // コールバック関数がセットされていればコールバック実行する
                callback(this);
            }
            break;
        }
        default:
            break;
    }
    return true;
}

/**
 *  キャッシュファイルを削除する
 *
 *  @param filename ファイル名
 *  @return 正常終了はtrue、それ以外はfalse
 */
bool DownloadCacheManager::removeCacheData(std::string filename)
{
    std::string filePath = FileUtils::getInstance()->getWritablePath() + filename;
    int ret = remove(filePath.c_str());
    return (ret == 0);
}
