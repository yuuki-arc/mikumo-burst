//
//  appCMatchAppDelegate.h
//  appC
//

#import <Foundation/Foundation.h>

/**
 * @brief MatchApp Protocol
 */
@protocol appCMatchAppDelegate <NSObject>
@optional

- (void)onGetMatchAppWithAppName:(NSString *)app_name
                     description:(NSString *)description
                         caption:(NSString *)caption
                            icon:(UIImage *)icon
                          banner:(UIImage *)banner;

- (void)onGetMatchAppWithIndex:(NSInteger)index
                       appName:(NSString *)app_name
                    description:(NSString *)description
                       caption:(NSString *)caption
                          icon:(UIImage *)icon
                        banner:(UIImage *)banner;

@end
