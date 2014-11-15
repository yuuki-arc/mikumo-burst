//
//  appCButtonView.h
//

#import <UIKit/UIKit.h>

/**
 * @brief appC ボタン型のビュー
 */
@interface appCButtonView : UIView

/**
 * @brief ViewController内の位置を指定して初期化
 *
 * 位置と画像を指定して、ボタン型の作成を行う
 *
 * @param controller_ 配置先のビューコントローラ
 * @param position_ 配置する位置
 * @param image_normal_ 通常時の画像を指定
 * @param image_highlighted_ タップ時の画像を指定（nilで省略可能）
 * @return 初期化されたインスタンス
 */
-(id)initWithViewController:(UIViewController*)controller_
	position:(CGPoint)position_
	imageNormal:(UIImage*)image_normal_
	imageHighlighted:(UIImage*)image_highlighted_
	;

/**
 * @brief ボタン座標の変更を行う
 *
 * @param button_position_ 位置
 */
-(void)changeButtonPosition:(CGPoint)button_position_;

/**
 * @brief 通常時の画像を変更する
 *
 * @param image_ 画像
 */
-(void)changeImageNormal:(UIImage*)image_;

/**
 * @brief 選択時の画像を変更する
 *
 * @param image_ 画像
 */
-(void)changeImageHighlighted:(UIImage*)image_;

/**
 * @brief 画像を変更する
 *
 * @param image_normal_ 通常時の画像
 * @param image_highlighted_ タップ時の画像
 */
-(void)changeImageNormal:(UIImage*)image_normal_ highlighted:(UIImage*)image_highlighted_;


@end
