//
//  TitleScene.cpp
//

#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

SEL_MenuHandler TitleScene::onResolveCCBCCMenuItemSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    return NULL;
}

Control::Handler TitleScene::onResolveCCBCCControlSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedStartButton", TitleScene::tappedStartButton);
    return NULL;
}

void TitleScene::tappedStartButton(Object * pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedStartButton eventType = %d", pControlEventType);
}
