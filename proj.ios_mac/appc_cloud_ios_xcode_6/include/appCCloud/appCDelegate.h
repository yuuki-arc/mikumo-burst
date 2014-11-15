//
//  appCDelegate.h
//  appC
//

#import <Foundation/Foundation.h>
#import "appCInAppPurchaseProduct.h"

@protocol appCDelegate <NSObject>

@optional

/**
 * @brief setupAppCWithMediaKey の完了通知
 *
 * @param succeed 成功・失敗フラグ
 */
- (void)finishedSetupAppC:(BOOL)succeed;

/**
 * @brief アプリ内課金：購入完了デリゲートメソッド
 *
 * @param productIdentifier プロダクトID
 */
- (void)inAppPurchased:(appCInAppPurchaseProduct *)productIdentifier;

/**
 * @brief アプリ内課金：購入失敗デリゲートメソッド
 *
 * @param productIdentifier プロダクトID
 * @param error エラー情報
 */
- (void)inAppPurchaseFailed:(appCInAppPurchaseProduct *)productIdentifier
                      error:(NSError *)error;

/**
 * @brief アプリ内課金：リストア通知
 *
 * @param productIdentifier プロダクトID
 */
- (void)inAppPurchaseRestored:(appCInAppPurchaseProduct *)productIdentifier;

/**
 * @brief アプリ内課金：リストア処理完了
 *
 */
- (void)inAppPurchaseRestoreCompleted;

/**
 * @brief アプリ内課金：リストア処理失敗
 *
 * @param error エラー情報
 */
- (void)inAppPurchaseRestoreFailed:(NSError *)error;

/**
 * @brief サービス獲得
 *
 * @param service_id サービスID
 */
- (void)getService:(NSString *)service_id;

@end
