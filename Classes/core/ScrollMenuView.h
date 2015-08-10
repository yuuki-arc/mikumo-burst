#ifndef __mikumo_burst__ScrollMenuView__
#define __mikumo_burst__ScrollMenuView__

#include <cocos2d.h>
#include "ScrollMenu.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ScrollMenuView : public ScrollView {
private:
    // タッチ開始時の座標
    Vec2 _touchStartPoint;
    // メニューオブジェクト
    ScrollMenu* _scrollMenu;
    
protected:
    // コンストラクタ
    ScrollMenuView();
    // オブジェクト作成時実行処理
    bool init(ScrollMenu* menu);
    // スクロール速度デアクセラレーション
    void deaccelerateScrolling(float dt);
    
public:

    virtual ~ScrollMenuView();

    // オブジェクト作成用function
    static ScrollMenuView* create(Size size, Node* container = NULL);
    static ScrollMenuView* create();
    static ScrollMenuView* create(ScrollMenu* menu);
    
    // オーバーライドするタッチ開始イベント
    bool onTouchBegan(Touch *touch, Event *unusedEvent) override;
    // オーバーライドするタッチ移動後イベント
    void onTouchMoved(Touch *touch, Event *unusedEvent) override;
    // オーバーライドするタッチ終了イベント
    void onTouchEnded(Touch *touch, Event *event) override;
};

#endif /* defined(__mikumo_burst__ScrollMenuView__) */
