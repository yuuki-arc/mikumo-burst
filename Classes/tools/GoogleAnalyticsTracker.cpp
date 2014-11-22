#include "tools/GoogleAnalyticsTracker.h"
#include "tools/GoogleAnalyticsTracker_JNI.h"

void GoogleAnalyticsTracker::sendScreen(const char* screenName)
{
    sendScreenJNI(screenName);
}
