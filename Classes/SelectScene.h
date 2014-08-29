#ifndef __SELECT_SCENE_H__
#define __SELECT_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

class SelectScene : public Layer
, public CCBSelectorResolver
{
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName);
    
    void tappedBattleButton(Ref* pTarget, Control::EventType pControlEventType);
    
public:
    SelectScene();
    virtual ~SelectScene();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SelectScene, create);

    void pushBack(Ref* pSender);
};

#endif /* defined(__SELECT_SCENE_H__) */
