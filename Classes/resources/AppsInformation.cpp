#include "resources/AppsInformation.h"
#include "core/Constant.h"
#include "core/picojson.h"
#include "resources/DownloadCacheManager.h"
#include <fstream>

USING_NS_CC;

AppsInformation::AppsInformation()
: appsInfoCache(nullptr)
, scenarioCache(nullptr)
{
}

AppsInformation::~AppsInformation()
{
}

/**
 *  初期化処理
 *
 *  @return 正常終了はtrue、それ以外はfalse
 */
bool AppsInformation::init()
{
    // アプリ情報キャッシュ設定
    appsInfoCache = DownloadCacheManager::create();
    appsInfoCache->retain();
    appsInfoCache->setUrl(__SHEET_URL_APPS);
    appsInfoCache->setFileName(Constant::CACHE_FILE_APPS());
    appsInfoCache->setCallback([this](Ref *sender){setAppsInformation();});
    // シナリオ情報キャッシュ設定
    scenarioCache = DownloadCacheManager::create();
    scenarioCache->retain();
    scenarioCache->setUrl(__SHEET_URL_STORY);
    scenarioCache->setFileName(Constant::CACHE_FILE_STORY());
//    scenarioCache->setCallback([this](Ref *sender){replaceSelectScene();});
    return true;
}

/**
 *  アプリ情報がキャッシュファイルに存在するかチェックを行う
 *
 *  @return 存在する場合はtrue、存在しなければfalse
 */
bool AppsInformation::isExistCacheFile(const std::string &cacheFile)
{
    if (cacheFile == Constant::CACHE_FILE_APPS())
    {
        return appsInfoCache->isExistCacheFile();
    }
    else if (cacheFile == Constant::CACHE_FILE_APPS())
    {
        return scenarioCache->isExistCacheFile();
    }
    return false;
}

/**
 *  データを指定したURLから非同期でダウンロードしてメモリに保持する
 *
 *  @return 正常終了はtrue、それ以外はfalse
 */
bool AppsInformation::downloadData(const std::string &cacheFile)
{
    if (cacheFile == Constant::CACHE_FILE_APPS())
    {
        return appsInfoCache->downloadResponseData();
    }
    else if (cacheFile == Constant::CACHE_FILE_APPS())
    {
        return scenarioCache->downloadResponseData();
    }
    return false;
}

/**
 *  データを指定したURLから非同期でダウンロードしてキャッシュファイルに書き込む
 *
 *  @return 正常終了はtrue、それ以外はfalse
 */
bool AppsInformation::downloadAndWriteCacheData(const std::string &cacheFile)
{
    if (cacheFile == Constant::CACHE_FILE_APPS())
    {
        return appsInfoCache->downloadAndWriteCacheData();
    }
    else if (cacheFile == Constant::CACHE_FILE_APPS())
    {
        return scenarioCache->downloadAndWriteCacheData();
    }
    return false;
}

/**
 *  ダウンロード済みのデータをキャッシュファイルに書き込む
 *
 *  @return 正常終了はtrue、それ以外はfalse
 */
bool AppsInformation::writeCache(const std::string &cacheFile)
{
    if (cacheFile == Constant::CACHE_FILE_APPS())
    {
        return appsInfoCache->writeCache();
    }
    else if (cacheFile == Constant::CACHE_FILE_APPS())
    {
        return scenarioCache->writeCache();
    }
    return false;
}

/**
 *  アプリ情報をjsonオブジェクトから取得してセットする
 */
void AppsInformation::setAppsInformation()
{
    picojson::object& sheets = appsInfoCache->loader->jsonResult.get<picojson::object>();
    
    // アプリ情報
    picojson::array& sheetColumns = sheets[Constant::SHEET_NAME_AP_APPS()].get<picojson::array>();
    for (picojson::array::iterator it = sheetColumns.begin(); it != sheetColumns.end(); it++)
    {
        CCLOG("test");
        picojson::object& column = it->get<picojson::object>();
        std::string device = (std::string)column["device"].get<std::string>();
        if (device == Constant::SHEET_COLUMN_AP_APPS())
        {
            this->device = device;
            this->version = (std::string)column["version"].get<std::string>();
            this->updateVersionDate = (std::string)column["updateVersionDate"].get<std::string>();
            this->updateSheetDate = (std::string)column["updateSheetDate"].get<std::string>();
        }
    }
    CCLOG("apps: %s %s %s %s", this->device.c_str(), this->version.c_str(), this->updateSheetDate.c_str(), this->updateVersionDate.c_str());
    // ストーリー情報
    scenarioList.clear();
    sheetColumns = sheets[Constant::SHEET_NAME_AP_SCENARIO()].get<picojson::array>();
    for (picojson::array::iterator it = sheetColumns.begin(); it != sheetColumns.end(); it++)
    {
        StringMap map;
        picojson::object& column = it->get<picojson::object>();
        map["id"] = std::to_string((int)column["id"].get<double>());
        map["sheet_name"] = (std::string)column["sheet_name"].get<std::string>();
        map["title"] = (std::string)column["title"].get<std::string>();
        map["release_date"] = (std::string)column["release_date"].get<std::string>();
        scenarioList.push_back(map);
        CCLOG("%s %s %s", map["id"].c_str(), map["sheet_name"].c_str(), map["title"].c_str());
        CCLOG("%s", map["release_date"].c_str());
    }
}
