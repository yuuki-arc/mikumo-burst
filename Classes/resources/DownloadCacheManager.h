#ifndef __mikumo_burst__DownloadCacheManager__
#define __mikumo_burst__DownloadCacheManager__

#include "cocos2d.h"
#include "resources/JsonLoader.h"

USING_NS_CC;

class DownloadCacheManager : public cocos2d::Ref
{
public:
    DownloadCacheManager();
    virtual ~DownloadCacheManager();
    
    bool init();
    CREATE_FUNC(DownloadCacheManager);
    
    CC_SYNTHESIZE(std::string, url, Url);
    CC_SYNTHESIZE(std::string, fileName, FileName);
    
    void setCallback(const std::function<void(Ref*)> &callback);
    bool isExistCacheFile();
    bool downloadResponseData();
    bool downloadAndWriteCacheData();
    bool readCache();
    bool loadData();
    bool execCallback();
    bool execCallbackReferenceData();

    enum LoadStatus
    {
        BeforeLoad = 0, // ロード処理前
        DataDownload,   // データダウンロード中
        ReadError,      // ファイル読み込みエラー（エラー）
        ReadSuccess,    // ファイル読み込み成功
        LoadComplete,   // ロード処理完了
    };
    LoadStatus loadStatus;
    JsonLoader* loader;

private:
    std::function<void(Ref*)> callback;
};
#endif /* defined(__mikumo_burst__DownloadCacheManager__) */
