#include "SelectScene.h"
#include "BattleSceneLoader.h"

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

SEL_MenuHandler SelectScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    return NULL;
}

Control::Handler SelectScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBattleButton", SelectScene::tappedBattleButton);
    return NULL;
}

void SelectScene::tappedBattleButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedBattleButton eventType = %d", pControlEventType);
    Scene* scene = BattleSceneLoader::createScene();
    TransitionProgressInOut* trans = TransitionProgressInOut::create(1, scene);
    Director::getInstance()->replaceScene(trans);
}
