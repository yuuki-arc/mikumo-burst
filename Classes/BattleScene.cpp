#include "BattleScene.h"
#include "ResultSceneLoader.h"

BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}

SEL_MenuHandler BattleScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);

    return NULL;
}

Control::Handler BattleScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedResultButton", BattleScene::tappedResultButton);
    return NULL;
}

void BattleScene::tappedResultButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedResultButton eventType = %d", pControlEventType);
    Scene* scene = ResultSceneLoader::createScene();
    TransitionProgressInOut* trans = TransitionProgressInOut::create(1, scene);
    Director::getInstance()->replaceScene(trans);
}
