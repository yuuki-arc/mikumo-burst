//
//  appCCutinView.h
//

#import <UIKit/UIKit.h>

/**
 * @brief appC カットイン型のビュー
 */
@interface appCCutinView : UIView
<UIScrollViewDelegate>

/**
 * @brief ViewControllerを指定して初期化
 *
 * @param controller_ 配置先のビューコントローラ
 * @param close_target_ 閉じるボタンを押したときのコールバック先
 * @param close_action_ 閉じるボタンを押したときのコールバック先
 */
-(id)initWithViewController:(UIViewController*)controller_
	closeTarget:(id)close_target_
	closeAction:(SEL)close_action_
	;

/**
 * @brief ViewControllerと、コールバック先としてブロックを指定して初期化
 *
 * @param controller_ 配置先のビューコントローラ
 * @param close_block_ 閉じるボタンを押したときに実行するブロック
 */
-(id)initWithViewController:(UIViewController*)controller_
	closeBlock:(void (^)(id))close_block_
	;

@end
