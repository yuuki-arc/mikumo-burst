#ifndef __SELECT_STORY_SCENE_H__
#define __SELECT_STORY_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"
#include "core/ScrollMenuView.h"
#include "resources/AppsInformation.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

class SelectStoryScene : public Layer
, public CCBSelectorResolver
, public NodeLoaderListener
, public ScrollViewDelegate
{
public:
    SelectStoryScene();
    virtual ~SelectStoryScene();
    
    virtual bool init();
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName);
    virtual void onNodeLoaded(Node* pNode, NodeLoader* pNodeLoader);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SelectStoryScene, create);
    
    void scrollViewDidScroll(ScrollMenuView *view);

    void tappedBackButton(Ref* pTarget, Control::EventType pControlEventType);
    
    virtual void touchOn();
    virtual void touchOff();
    
    // シングルタッチイベント
    bool onTouchBegan(Touch* touch, Event *event);
    void onTouchMoved(Touch* touch, Event *event);
    void onTouchEnded(Touch* touch, Event *event);
    void onTouchCancelled(Touch* touch, Event *event);
    
    void pushBack(Ref* pSender);
    
private:
    enum ZOrder
    {
        Bg = 0,
        Status,
        Font,
    };

    //    EventListenerTouchAllAtOnce* listener;
    EventListenerTouchOneByOne* listener;
    void initTouchEvent();
    int difference(int,int);
    Sprite* map;

    Point currentpos,prevpos,velocity; //座標保存クラスと速度ベクトル管理クラス

    AppsInformation* appsInfo;
    ScrollMenuView* scrollView;
    
    void initMenu();
    void setupGame();
};

#endif /* defined(__SELECT_STORY_SCENE_H__) */
