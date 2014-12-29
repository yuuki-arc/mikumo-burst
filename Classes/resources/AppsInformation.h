#ifndef __mikumo_burst__AppsInformation__
#define __mikumo_burst__AppsInformation__

#include "core/Constant.h"
#include "resources/DownloadCacheManager.h"

USING_NS_CC;

class AppsInformation : public cocos2d::Ref
{
public:
    AppsInformation();
    virtual ~AppsInformation();

    bool init();
    CREATE_FUNC(AppsInformation);

    CC_SYNTHESIZE(std::string, device, Device);
    CC_SYNTHESIZE(std::string, version, Version);
    CC_SYNTHESIZE(std::string, updateVersionDate, UpdateVersionDate);
    CC_SYNTHESIZE(std::string, updateSheetDate, UpdateSheetDate);
    
    bool downloadData();
    void setAppsInformation();
    
    DownloadCacheManager* downloadCache;
    StringMapVector scenarioList;
};
#endif /* defined(__mikumo_burst__AppsInformation__) */
