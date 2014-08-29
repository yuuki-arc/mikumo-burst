#include "ResultScene.h"
#include "SelectSceneLoader.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

SEL_MenuHandler ResultScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);

    return NULL;
}

Control::Handler ResultScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedSelectButton", ResultScene::tappedSelectButton);
    return NULL;
}

void ResultScene::tappedSelectButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedSelectButton eventType = %d", pControlEventType);
    Scene* scene = SelectSceneLoader::createScene();
    TransitionProgressInOut* trans = TransitionProgressInOut::create(1, scene);
    Director::getInstance()->replaceScene(trans);
}
