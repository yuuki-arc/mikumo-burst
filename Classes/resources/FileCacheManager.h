#ifndef __mikumo_burst__FileCacheManager__
#define __mikumo_burst__FileCacheManager__

#include "cocos2d.h"
#include "resources/JsonLoader.h"

USING_NS_CC;

class FileCacheManager : public cocos2d::Ref
{
public:
    FileCacheManager();
    virtual ~FileCacheManager();
    
    bool init();
    CREATE_FUNC(FileCacheManager);
    
    CC_SYNTHESIZE(std::string, url, Url);
    CC_SYNTHESIZE(std::string, fileName, FileName);
    
    void setCallback(const std::function<void(Ref*)> &callback);
    bool loadData();
    bool readData();

    enum LoadStatus
    {
        BeforeLoad = 0,
        DataDownload,
        ReadError,
        ReadSuccess,
        LoadComplete,
    };
    LoadStatus loadStatus;
    JsonLoader* loader;

private:
    std::function<void(Ref*)> callback;
};
#endif /* defined(__mikumo_burst__FileCacheManager__) */
