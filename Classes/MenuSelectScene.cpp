#include "MenuSelectScene.h"
#include "TitleScene.h"

MenuSelectScene::MenuSelectScene()
{
}

MenuSelectScene::~MenuSelectScene()
{
}

SEL_MenuHandler MenuSelectScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    return NULL;
}

Control::Handler MenuSelectScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedStartButton", MenuSelectScene::tappedStartButton);
    return NULL;
}

void MenuSelectScene::tappedStartButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedStartButton eventType = %d", pControlEventType);
}
