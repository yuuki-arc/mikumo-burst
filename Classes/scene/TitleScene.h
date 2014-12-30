#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"
#include "resources/AppsInformation.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

class TitleScene : public Layer
, public CCBSelectorResolver
, public NodeLoaderListener
{
public:
    TitleScene();
    virtual ~TitleScene();
    
    virtual bool init();
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName);
	virtual void onNodeLoaded(Node* pNode, NodeLoader* pNodeLoader);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TitleScene, create);

    void update(float frame);
    void tappedStartButton(Ref* pTarget, Control::EventType pControlEventType);
    
    AppsInformation* appsInfo;
};

#endif /* defined(__TITLE_SCENE_H__) */
