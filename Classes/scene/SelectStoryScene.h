#ifndef __SELECT_STORY_SCENE_H__
#define __SELECT_STORY_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"
#include "core/ScrollViewWrapper.h"

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
    
    void scrollViewDidScroll(ScrollView *view);
    
    void tappedBackButton(Ref* pTarget, Control::EventType pControlEventType);
    
    void pushBack(Ref* pSender);
    
private:
    enum ZOrder
    {
        Bg = 0,
        Status,
        Font,
    };

    ScrollViewWrapper* scrollView;
};

#endif /* defined(__SELECT_STORY_SCENE_H__) */
