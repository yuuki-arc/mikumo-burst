#include "scene/MenuScene.h"
#include "scene/SelectSceneLoader.h"
#include "tools/GoogleAnalyticsTracker.h"
#include "core/Constant.h"
#include "resources/SoundManager.h"
#include "factory/TextCreator.h"
#include "tools/NativeLauncher.h"

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

bool MenuScene::init()
{
    GoogleAnalyticsTracker::sendScreen("MenuScene");
    if(!Layer::init())
    {
        return false;
    }
    
    return true;
}

SEL_MenuHandler MenuScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    return NULL;
}

Control::Handler MenuScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedInformationButton", MenuScene::tappedInformationButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedReviewButton", MenuScene::tappedReviewButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedCreditButton", MenuScene::tappedCreditButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBackButton", MenuScene::tappedBackButton);
    return NULL;
}

void MenuScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    // SE
    SoundManager* soundManager = new SoundManager();
    soundManager->preloadSE("se_select");
}

void MenuScene::tappedInformationButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedInformationButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    // お知らせサイトに遷移
    NativeLauncher::openUrl("http://yuukiar.co/apps/mikumo-burst/");
}

void MenuScene::tappedReviewButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedReviewButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    // アプリストアに遷移
    NativeLauncher::openStoreReview("");
}

void MenuScene::tappedCreditButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedCreditButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    // クレジット表記
}

void MenuScene::tappedBackButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedBackButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    
    Scene* scene = SelectSceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}
