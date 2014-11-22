#ifndef ___10sec_BURST__GoogleAnalyticsTracker__
#define ___10sec_BURST__GoogleAnalyticsTracker__

#include "cocos2d.h"

class GoogleAnalyticsTracker
{
public:
    
    /**GoogleAnalyticsへのデータ送信処理を初期化します。*/
    static void setup();
    
    /**
     GoogleAnalyticsにスクリーントラッキング情報を送信します。
     
     @param screenName スクリーン名。
     */
    static void sendScreen(const char* screenName);
};

#endif /* defined(___10sec_BURST__GoogleAnalyticsTracker__) */
