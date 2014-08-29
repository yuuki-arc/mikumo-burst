#include "TitleScene.h"
#include "MenuSelectSceneLoader.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

SEL_MenuHandler TitleScene::onResolveCCBCCMenuItemSelector(Ref *pTarget, const char *pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    return NULL;
}

Control::Handler TitleScene::onResolveCCBCCControlSelector(Ref *pTarget, const char *pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedStartButton", TitleScene::tappedStartButton);
    return NULL;
}

void TitleScene::tappedStartButton(Ref *pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedStartButton eventType = %d", pControlEventType);
    Scene* scene = MenuSelectSceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(1, scene);
    Director::getInstance()->replaceScene(trans);
}

