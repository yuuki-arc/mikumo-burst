#ifndef __RESULT_SCENE_H__
#define __RESULT_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

class ResultScene : public Layer
, public CCBSelectorResolver
{
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName);

    void tappedStartButton(Ref* pTarget, Control::EventType pControlEventType);

public:
    ResultScene();
    virtual ~ResultScene();

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ResultScene, create);

    void pushBack(Ref* pSender);
};

#endif /* defined(__Result_SCENE_H__) */
