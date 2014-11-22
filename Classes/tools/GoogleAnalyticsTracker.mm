#import "tools/GoogleAnalyticsTracker.h"
#import "GAI.h"
#import "GAIDictionaryBuilder.h"
#import "GAIFields.h"

#define GA_TRACKING_ID "UA-34476431-8"

void GoogleAnalyticsTracker::setup()
{
    // Optional: automatically send uncaught exceptions to Google Analytics.
    [GAI sharedInstance].trackUncaughtExceptions = YES;
    
    // Optional: set Google Analytics dispatch interval to e.g. 20 seconds.
    [GAI sharedInstance].dispatchInterval = 20;
    
    // Optional: set Logger to VERBOSE for debug information.
    [[[GAI sharedInstance] logger] setLogLevel:kGAILogLevelVerbose];
    
    // Initialize tracker. Replace with your tracking ID.
    [[GAI sharedInstance] trackerWithTrackingId:[NSString stringWithUTF8String:GA_TRACKING_ID]];
}

void GoogleAnalyticsTracker::sendScreen(const char* screenName)
{
    // May return nil if a tracker has not already been initialized with a
    // property ID.
    id tracker = [[GAI sharedInstance] defaultTracker];
    
    // This screen name value will remain set on the tracker and sent with
    // hits until it is set to a new value or to nil.
    [tracker set:kGAIScreenName value:[NSString stringWithUTF8String:screenName]];
    
    [tracker send:[[GAIDictionaryBuilder createScreenView] build]];
}
