#include "resources/AppsInformation.h"
#include "core/Constant.h"
#include "core/picojson.h"
#include "resources/DownloadCacheManager.h"
#include <fstream>

USING_NS_CC;

AppsInformation::AppsInformation()
: downloadCache(nullptr)
{
}

AppsInformation::~AppsInformation()
{
}

/**
 *  初期化処理
 *
 *  @param mode キャッシュ場所をファイルかメモリかを指定する（デフォルトはファイル）
 *  @return 正常終了はtrue、それ以外はfalse
 */
bool AppsInformation::init(DownloadCacheMode mode)
{
    downloadCache = DownloadCacheManager::create();
    downloadCache->retain();
    downloadCache->setUrl(__SHEET_URL_APPS);
    downloadCache->setFileName(Constant::CACHE_FILE_APPS());
    downloadCache->setCallback([this](Ref *sender){setAppsInformation();});
    return true;
}

/**
 *  データを指定したURLから非同期でダウンロードしてメモリに保持する
 *
 *  @return 正常終了はtrue、それ以外はfalse
 */
bool AppsInformation::downloadData()
{
    downloadCache->downloadResponseData();
    return true;
}

/**
 *  データを指定したURLから非同期でダウンロードしてキャッシュファイルに書き込む
 *
 *  @return 正常終了はtrue、それ以外はfalse
 */
bool AppsInformation::downloadAndWriteCacheData()
{
    downloadCache->downloadAndWriteCacheData();
    return true;
}

/**
 *  アプリ情報をjsonオブジェクトから取得してセットする
 */
void AppsInformation::setAppsInformation()
{
    picojson::object& sheets = downloadCache->loader->jsonResult.get<picojson::object>();
    
    // アプリ情報
    picojson::array& sheetColumns = sheets[Constant::SHEET_NAME_AP_APPS()].get<picojson::array>();
    for (picojson::array::iterator it = sheetColumns.begin(); it != sheetColumns.end(); it++)
    {
        CCLOG("test");
        picojson::object& column = it->get<picojson::object>();
        std::string device = (std::string)column["device"].get<std::string>();
        if (device == Constant::SHEET_COLUMN_AP_APPS())
        {
            CCLOG("test-OK %s", device.c_str());
            CCLOG("test-OK %s", getDevice().c_str());
            CCLOG("test-OK %s", this->device.c_str());
            setDevice(device);
            setVersion((std::string)column["version"].get<std::string>());
            setUpdateVersionDate((std::string)column["updateVersionDate"].get<std::string>());
            setUpdateSheetDate((std::string)column["updateSheetDate"].get<std::string>());
        }
    }
    CCLOG("apps: %s %s %s %s", getDevice().c_str(), getVersion().c_str(), getUpdateSheetDate().c_str(), getUpdateVersionDate().c_str());
    CCLOG("device: %s", device.c_str());
    CCLOG("constant: %s", Constant::SHEET_COLUMN_AP_APPS());
    // ストーリー情報
    scenarioList.clear();
    sheetColumns = sheets[Constant::SHEET_NAME_AP_SCENARIO()].get<picojson::array>();
    for (picojson::array::iterator it = sheetColumns.begin(); it != sheetColumns.end(); it++)
    {
        StringMap map;
        picojson::object& column = it->get<picojson::object>();
        map["id"] = (std::string)column["id"].get<std::string>();
        map["sheet_name"] = (std::string)column["sheet_name"].get<std::string>();
        map["title"] = (std::string)column["title"].get<std::string>();
        map["release_date"] = (std::string)column["release_date"].get<std::string>();
        scenarioList.push_back(map);
        CCLOG("%s %s %s %s", map["id"].c_str(), map["sheet_name"].c_str(), map["title"].c_str(), map["release_date"].c_str());
    }
}
