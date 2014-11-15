//
//  appCCloud.h
//

#import "appC.h"
#import "appCCloudDefine.h"
#import "appCDelegate.h"

/*
 Push通知を利用する場合は AppDelegate.m 内に次の処理を実装してください。
 ----------------------------------------
 - (void)application:(UIApplication *)app didRegisterForRemoteNotificationsWithDeviceToken:(NSData *) devToken
 {
    [appCCloud pushNotificationDidRegisterWithDeviceToken:devToken];
 }
 
 - (void)application:(UIApplication *)app didFailToRegisterForRemoteNotificationsWithError:(NSError *) err
 {
    [appCCloud pushNotificationDidFailWithError:err];
 }
 
 - (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
 {
    [appCCloud pushNotificationDidReceive:userInfo appStat:application.applicationState];
 }
 ----------------------------------------
 */


/**
 * @brief appC Cloudのエントリクラス
 *
 */
@interface appCCloud : appC

/**
 * @brief メディアキーを指定してappCを初期設定する
 *
 * @param mk_ メディアキー
 * @param option_ オプション
 *
 */
+(void)setupAppCWithMediaKey:(NSString*)mk_
                      option:(NSUInteger)option_;

/**
 * @brief メディアキーを指定してappCを初期設定する
 *
 * @param mk_ メディアキー
 * @param option_ オプション
 * @param launchOptions_ ランチオプション
 *
 */
+(void)setupAppCWithMediaKey:(NSString*)mk_
                      option:(NSUInteger)option_
               launchOptions:(NSDictionary *)launchOptions_;

/**
 * @brief リカバリを開始する
 *
 */
+(void)startRecovery;

/**
 * @brief delegate設定
 *
 * @param delegate appCDelegate
 */
+ (void)setDelegate:(id<appCDelegate>)delegate;


////////////////////////////////////////
// for Gamsers

/**
 * @brief 有効LB設定
 * setupAppCWithMediaKey より前でコールしてください。
 * コールしない場合は管理画面で登録された全てのリーダーボードが有効となります。
 *
 * @param リーダーボードIDの配列
 */
+ (BOOL)gamersSetActiveLbs:(NSArray *)lb_ids;

/**
 * @brief LB取得（全データ）
 *
 * @return LB全データ
 */
+ (NSArray *)gamersGetAllLbData;


////////////////////////////////////////
// for Push 通知

/**
 * @brief Notificationの登録完了を通知する
 *
 */
+(void)pushNotificationDidRegisterWithDeviceToken:(NSData*)token;

/**
 * @brief Notificationの登録失敗を通知する
 *
 */
+(void)pushNotificationDidFailWithError:(NSError *)error;


/**
 * @brief Notificationの受信を通知する
 *
 */
+(void)pushNotificationDidReceive:(NSDictionary *)userInfo
                          appStat:(UIApplicationState)appStat;


////////////////////////////////////////
// for DataStore

/**
 * @brief 有効DataStore設定
 * setupAppCWithMediaKey より前でコールしてください。
 * コールしない場合は管理画面で登録された全てのDataStoreが有効となります。
 *
 * @param DataStore keyの配列
 */
+ (BOOL)dataStoreSetActiveKeys:(NSArray *)keys;

/**
 * @brief DataStore現在値取得（整数）
 *
 * @param key キー
 * @return 現在値
 */
+ (NSInteger)dataStoreIntegerWithKey:(NSString *)key;

/**
 * @brief DataStore現在値取得（文字列）
 *
 * @param key キー
 * @return 現在値
 */
+ (NSString *)dataStoreStringWithKey:(NSString *)key;

/**
 * @brief DataStore現在値設定（整数）
 *
 * @param key キー
 * @param value 値
 * @return YES:成功
 */
+ (BOOL)dataStoreSetIntegerWithKey:(NSString *)key
                           integer:(NSInteger)value;

/**
 * @brief DataStore現在値設定（文字列）
 *
 * @param key キー
 * @param value 値
 * @return YES:成功
 */
+ (BOOL)dataStoreSetStringWithKey:(NSString *)key
                           string:(NSString *)value;

/**
 * @brief DataStore現在値取得（全データ）
 *
 * @return DataStore全データ
 */
+ (NSArray *)dataStoreGetAllData;


////////////////////////////////////////
// for PURCHASE

/**
 * @brief アプリ内課金アイテムリスト画面表示
 *
 * @return 実行可否
 */
+ (BOOL)purchaseShowList;

/**
 * @brief アプリ内課金復元処理開始
 *
 * @return 実行可否
 */
+ (BOOL)purchaseRestore;

/**
 * @brief PURCHASE有効アイテム追加
 * setupAppCWithMediaKey より前でコールしてください。
 * コールしない場合は管理画面で登録された全てのアイテムが有効となります。
 *
 * @param category_key カテゴリーキー
 * @param product_ids プロダクトIDの配列
 */
+ (BOOL)purchaseAddActiveKey:(NSString *)category_key ids:(NSArray *)product_ids;

/**
 * @brief PURCHASEアイテム数削減
 *
 * @param category_key カテゴリーキー
 * @param reduce 削減数
 * @return アイテム数削減後の総数（エラー時は-1）
 */
+ (NSInteger)purchaseUseCountWithKey:(NSString *)category_key
                              reduce:(NSInteger)reduce;

/**
 * @brief PURCHASEアイテム数設定
 *
 * @param category_key カテゴリーキー
 * @param count アイテム数
 * @return アイテム数設定後の総数（エラー時は-1）
 */
+ (NSInteger)purchaseSetCountWithKey:(NSString *)category_key
                               count:(NSInteger)count;

/**
 * @brief PURCHASEアイテム数取得
 *
 * @param category_key カテゴリーキー
 * @return アイテム数（エラー時は-1）
 */
+ (NSInteger)purchaseGetCountWithKey:(NSString *)category_key;

/**
 * @brief PURCHASEアイテム取得（全データ）
 *
 * @return PURCHASEアイテム全データ
 */
+ (NSArray *)purchaseGetAllData;

////////////////////////////////////////
// for Reward

/**
 * @brief リワードリスト画面表示（自サービス用）
 *
 * @param service_id サービスID
 * @return 実行可否
 */
+ (BOOL)rewardShowListServiceWithId:(NSString *)service_id;

/**
 * @brief リワードリスト画面表示（ポイント）
 *
 * @return 実行可否
 */
+ (BOOL)rewardShowListPoint;


/**
 * @brief 成果予約を行う
 *
 * @param app_id_ アプリID
 */
//+(void)registCpiWithAppId:(NSString*)app_id_
//                 adAppsId:(NSString*)ad_apps_id_
//                 redirect:(NSString*)redirect_
//                urlScheme:(NSString*)url_scheme_
//                  linkTag:(NSString*)link_tag_
//                 comicCid:(NSString*)comic_Cid_
//;


/**
 * @brief ユーザID返却
 *
 * @return ユーザID
 */
//+ (NSString *)userId;

@end
