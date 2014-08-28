#include "HomeScene.h"
#include "TitleScene.h"

HomeScene::HomeScene()
{
}

HomeScene::~HomeScene()
{
}

SEL_MenuHandler HomeScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    return NULL;
}

Control::Handler HomeScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedStartButton", HomeScene::tappedStartButton);
    return NULL;
}

void HomeScene::tappedStartButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedStartButton eventType = %d", pControlEventType);
}
