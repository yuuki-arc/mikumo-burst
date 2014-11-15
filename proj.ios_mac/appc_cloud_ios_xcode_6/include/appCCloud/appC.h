//
//  appC.h
//

#import <Foundation/Foundation.h>
#import "appCSimpleView.h"
#import "appCMoveIconView.h"
#import "appCMarqueeView.h"
#import "appCButtonView.h"
#import "appCCutinView.h"
#import "appCMatchAppDelegate.h"

/**
 * @brief appCのエントリクラス
 *
 */
@interface appC : NSObject

/**
 * @brief メディアキーを指定してappCを初期設定する
 *
 * @param mk_ メディアキー
 *
 */
+(void)setupAppCWithMediaKey:(NSString*)mk_;

////////////////////////////////////////
// for CPI

/**
 * @brief appCWebViewを表示する
 *
 */
+(void)openWebView;

/**
 * @brief appCWebVew表示中取得
 *
 */
+(BOOL)showingWebView;

/**
 * @brief 広告実行中取得
 *
 */
+(BOOL)showingAd;

/**
 * @brief appCMatchAppの利用を開始する（単体）
 *
 * @param delegate デリゲート
 */
+(void)matchAppStartWithDelegate:(id<appCMatchAppDelegate>)delegate;

/**
 * @brief appCMatchAppの利用を開始する（複数）
 *
 * @param delegate デリゲート
 * @param count 要求広告数
 */
+(void)matchAppStartWithDelegate:(id<appCMatchAppDelegate>)delegate
                           count:(NSInteger)count;

/**
 * @brief appCMatchAppの利用を終了する
 *
 */
+(void)matchAppStop;

/**
 * @brief appCMatchAppのコントロールを登録する(UIButtonなど)
 *
 * @param control ボタン
 */
+(void)matchAppRegistWithControl:(UIControl *)control;

/**
 * @brief appCMatchAppのコントロールを登録する(UIButtonなど)
 *
 * @param control ボタン
 * @param index インデックス
 */
+(void)matchAppRegistWithControl:(UIControl *)control
                           index:(NSInteger)index;

/**
 * @brief バナー広告表示
 *
 * @param vertical_ 垂直位置
 */
+ (BOOL)matchAppShowBannerWithHorizontal:(appCHorizontal)horizontal
                                vertical:(appCVertical)vertical;

/**
 * @brief バナー広告消去
 *
 */
+ (BOOL)matchAppHideBanner;

/**
 * @brief Cutin表示中を取得する
 *
 * @return YES:Cutin表示中
 */
+(BOOL)showingCutin;

/**
 * @brief リリースステータスを取得する
 *
 * @return 0:開発中
 *         1:申請中
 *         2:リリース済
 */
+(int)getReleaseStatus;

    /**
 * @brief Webスプラッシュ画面のappC cloudロゴ表示・非表示
 *
 * @param splash_logo_ YES:表示(Default)、NO:非表示
 */
+(void)setSplashLogo:(BOOL)splash_logo_;


////////////////////////////////////////
// for Gamsers

/**
 * @brief appC Gamers を表示する
 *
 */
+(BOOL)openGamers;

/**
 * @brief ゲーム開始
 *
 */
+(BOOL)gamersStartGame;

/**
 * @brief Nickname取得
 *
 * @return Nickname
 */
+(NSString*)gamersGetNickname;

/**
 * @brief プレー回数加算
 *
 */
+(BOOL)gamersPlayCountIncrement;

/**
 * @brief プレー回数取得
 *
 * @return プレー回数
 */
+(NSInteger)gamersGetPlayCount;

/**
 * @brief 通知メッセージ表示
 *
 * @param title メッセージ
 * @param iconUrl アイコン画像URL
 * @param skinColor 背景色
 * @param textColor 文字色
 * @param duration 表示時間
 */
+(BOOL)gamersShowNotificationWithTitle:(NSString*)title
                               iconUrl:(NSString*)iconUrl
                             skinColor:(NSString*)skinColor
                             textColor:(NSString*)textColor
                              duration:(CGFloat)duration;

/**
 * @brief LBスコア登録（整数）
 *
 * @param lb_id リーダーボードID
 * @param score スコア
 */
+(BOOL)gamersAddLbWithId:(NSInteger)lb_id
                  scorei:(NSInteger)score;

/**
 * @brief LBスコア登録（小数）
 *
 * @param lb_id リーダーボードID
 * @param score スコア
 */
+(BOOL)gamersAddLbWithId:(NSInteger)lb_id
                  scored:(CGFloat)score;

/**
 * @brief LBデータ取得(JSON)
 *
 * @param lb_id リーダーボードID
 * @return LBデータ(JSON)
 */
+(NSString*)gamersGetLbWithId:(NSInteger)lb_id;

@end
