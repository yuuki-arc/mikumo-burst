#include "GoogleAnalyticsTracker.h"
#include "GoogleAnalyticsTracker_JNI.h"

void GoogleAnalyticsTracker::sendScreen(const char* screenName)
{
    sendScreenJNI(screenName);
}
