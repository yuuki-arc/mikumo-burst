#ifndef __SCORE_SCENE_H__
#define __SCORE_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

class ScoreScene : public Layer
, public CCBSelectorResolver
, public NodeLoaderListener
{
public:
    ScoreScene();
    virtual ~ScoreScene();
    
    virtual bool init();
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName);
    virtual void onNodeLoaded(Node* pNode, NodeLoader* pNodeLoader);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ScoreScene, create);
    
    void tappedScoreButton(Ref* pTarget, Control::EventType pControlEventType);
    void tappedBackButton(Ref* pTarget, Control::EventType pControlEventType);
    
    void pushBack(Ref* pSender);
    
private:
    enum ZOrder
    {
        Bg = 0,
        Status,
        Font,
    };
};

#endif /* defined(__Score_SCENE_H__) */
