//
//  appCMoveIconView.h
//

#import <UIKit/UIKit.h>
#import "appCDefine.h"

/**
 * @brief appC シンプル型のビュー
 */
@interface appCMoveIconView : UIView

/**
 * @brief ViewController内の上部に配置されるように初期化
 *
 * ビューコントローラの上部に張り付くように配置するためには、このインタフェースで初期化を行う<br>
 * 引数に配置する先となるビューコントロラーを指定する
 *
 * @param controller_ 配置先のビューコントローラ
 * @return 初期化されたインスタンス
 */
-(id)initWithTopWithViewController:(UIViewController*)controller_;

/**
 * @brief ViewController内の下部に配置されるように初期化
 *
 * ビューコントローラの下部に張り付くように配置するためには、このインタフェースで初期化を行う<br>
 * 引数に配置する先となるビューコントロラーを指定する
 *
 * @param controller_ 配置先のビューコントローラ
 * @return 初期化されたインスタンス
 */
-(id)initWithBottomWithViewController:(UIViewController*)controller_;

/**
 * @brief ViewController内の位置を指定して初期化
 *
 * ビューコントローラ内の指定した位置に設置する場合は、このインタフェースで初期化を行う<br>
 * 引数に配置する位置と、配置先となるビューコントロラーを指定する
 *
 * @param point_ 配置する位置
 * @param controller_ 配置先のビューコントローラ
 * @return 初期化されたインスタンス
 */
-(id)initWithPosition:(CGPoint)point_ viewController:(UIViewController*)controller_;

/**
 * @brief ViewController内の指定位置に配置されるように初期化
 *
 * 表示位置を指定して配置するためには、このインタフェースで初期化を行う<br>
 * 引数に配置する先となるビューコントローラと表示位置を指定する
 *
 * @param controller_ 配置先のビューコントローラ
 * @param horizontal_ 水平位置
 * @param vertical_ 垂直位置
 * @return 初期化されたインスタンス
 */
-(id)initWithViewController:(UIViewController*)controller_
                 horizontal:(appCHorizontal)horizontal_
                   vertical:(appCVertical)vertical_;

@end
