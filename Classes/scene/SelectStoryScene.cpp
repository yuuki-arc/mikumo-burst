#include "scene/SelectStoryScene.h"
#include "scene/SelectSceneLoader.h"
#include "tools/GoogleAnalyticsTracker.h"
#include "core/Constant.h"
#include "core/GameManager.h"
#include "factory/CharacterCreator.h"
#include "resources/SoundManager.h"
#include "factory/TextCreator.h"
#include "core/ScrollViewWrapper.h"

#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

SelectStoryScene::SelectStoryScene()
{
}

SelectStoryScene::~SelectStoryScene()
{
}

bool SelectStoryScene::init()
{
    GoogleAnalyticsTracker::sendScreen("SelectStoryScene");
    if(!Layer::init())
    {
        return false;
    }
    
    return true;
}

SEL_MenuHandler SelectStoryScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    return NULL;
}

Control::Handler SelectStoryScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBackButton", SelectStoryScene::tappedBackButton);
    return NULL;
}

void SelectStoryScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    // SE
    SoundManager* soundManager = new SoundManager();
    soundManager->preloadSE("se_select");

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // レイヤー
    Layer *layer = LayerColor::create();
    layer->setAnchorPoint(Point::ZERO);
    layer->setPosition(Point::ZERO);
    layer->setColor(Color3B::BLUE);
    layer->setOpacity(128);
    
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
//    auto *button = Sprite::create("syber2.png");
//    layer->addChild(button);
    
    //画面サイズでスクロールビューを作る
    layer->setContentSize(visibleSize);
    scrollView = ScrollViewWrapper::create(visibleSize);
    scrollView->setDelegate(this);
    scrollView->setContentSize(layer->getContentSize());
    scrollView->setContainer(layer);

    scrollView->setPosition(Point(origin.x + visibleSize.height * 10 / 100,
                                  origin.y + visibleSize.height * 20 / 100));
//    scrollView->setScale(scrollView->getScale(),
//                           scrollView->getScale() * 4 / 10);
//    
//    auto point = Point(origin.x + visibleSize.width / 2,
//                       origin.y + visibleSize.height * 90 / 100);
//    scrollView->setPosition(point);
//    scrollView->setContentOffset(Point::ZERO);
    scrollView->setDirection(ScrollView::Direction::VERTICAL);
    scrollView->setBounceable(true);
    scrollView->setViewSize(Size(visibleSize.width * 80 / 100,
                                 visibleSize.height * 60 / 100));
    this->addChild(scrollView);
//    scrollBarView = ScrollBarView::create(scrollView, ScrollBarView::BarType::VERTICAL_IN);
    CCLOG("test");
    
    // 初期のズームサイズ
    //    scrollView->setZoomScale(1.0f);
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
void SelectStoryScene::scrollViewDidScroll(ScrollView *view)
{
    log("スクロール！");
}

void SelectStoryScene::tappedBackButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedBackButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    
    Scene* scene = SelectSceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}
