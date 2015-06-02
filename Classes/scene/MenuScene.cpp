#include "scene/MenuScene.h"
#include "scene/SelectSceneLoader.h"
#include "tools/GoogleAnalyticsTracker.h"
#include "core/Constant.h"
#include "core/GameManager.h"
#include "factory/CharacterCreator.h"
#include "resources/SoundManager.h"
#include "factory/TextCreator.h"
#include "tools/NativeLauncher.h"

#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

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

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    // レイヤー
    Layer *layer = Layer::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(Point::ZERO);
    
    // on layer
    Constant::StringVector personaList = Constant::PERSONA_IMAGE_LIST(Constant::ImagePersona::PersonaSelect);
    int num = GameManager::getInstance()->getCharaSelect();
    std::string personaFileName = StringUtils::format("%s.png", personaList[num].c_str());
    Point charaPos = Point(origin.x + visibleSize.width * 2 / 3,
                           origin.y + visibleSize.height * 65 / 100);
    CharacterCreator* creator = new CharacterCreator();
    creator->init(CharacterScale::HARF);
    Sprite* character = creator->create(personaFileName, charaPos);
    layer->addChild(character);
    
    // on layer
    auto *button = Sprite::create("freebu32_4.png");
    layer->addChild(button);
    
    //画面サイズでスクロールビューを作る
    layer->setContentSize(visibleSize);
    auto scrollView = ScrollView::create(visibleSize);
    scrollView->setDelegate(this);
    scrollView->setContentSize(button->getContentSize());
    scrollView->setContainer(layer);
    scrollView->setPosition(Point::ZERO);
    scrollView->setContentOffset(Point::ZERO);
    scrollView->setDirection(ScrollView::Direction::VERTICAL);
    scrollView->setBounceable(true);
    scrollView->setViewSize(Size(500, 500));

    this->addChild(scrollView);
    // 初期のズームサイズ
//    scrollView->setZoomScale(1.0f);
    
    // ビュー初期位置（以下はレイヤー中心の例）
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Point origin = Director::getInstance()->getVisibleOrigin();
//    auto point = Point(origin.x + visibleSize.width / 2,
//                       origin.y + visibleSize.height * 45 / 100);
//    scrollView->setContentOffset(point);
//
//    scrollView->setMinScale(0.5f);
//    scrollView->setMaxScale(2.0f);
//
}

// スクロール
void MenuScene::scrollViewDidScroll(ScrollView *view)
{
    log("スクロール！");
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
