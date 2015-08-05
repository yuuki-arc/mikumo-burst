#include "scene/SelectStoryScene.h"
#include "scene/SelectSceneLoader.h"
#include "tools/GoogleAnalyticsTracker.h"
#include "core/Constant.h"
#include "core/GameManager.h"
#include "factory/CharacterCreator.h"
#include "resources/SoundManager.h"
#include "factory/TextCreator.h"
#include "core/ScrollViewWrapper.h"
#include "resources/AppsInformation.h"

#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

SelectStoryScene::SelectStoryScene()
: appsInfo(nullptr)
{
}

SelectStoryScene::~SelectStoryScene()
{
    CC_SAFE_RELEASE_NULL(appsInfo);
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

    // ストーリー情報取得
    appsInfo = AppsInformation::create();
    appsInfo->scenarioCache->readCache();

    // マップ画像を定義
    // テクスチャアトラスを読み込む
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("map/map.plist");
    Sprite* map = Sprite::createWithSpriteFrameName("25120762_p0.jpg");

    float mapContentSizeW = map->getContentSize().width * Constant::WORLD_MAP_SCALE;
    float mapContentSizeH = map->getContentSize().height * Constant::WORLD_MAP_SCALE;
    
    map->setScale(Constant::WORLD_MAP_SCALE);
    map->setAnchorPoint(Point::ANCHOR_MIDDLE);
    map->setPosition(Point(mapContentSizeW * 1 / 2,
                           mapContentSizeH * 1 / 2));

    // マップオブジェクト定義
    Sprite* mapObj = Sprite::createWithSpriteFrameName("pipo-map001.png");
    mapObj->setScale(Constant::WORLD_MAP_SCALE);
    mapObj->setAnchorPoint(Point::ANCHOR_MIDDLE);
    mapObj->setPosition(Point(mapContentSizeW * 1 / 2,
                              mapContentSizeH * 1 / 2));
    

    // マップ画像を包括するレイヤーを定義
    Layer *layer = LayerColor::create();
//    layer->setAnchorPoint(Point::ANCHOR_MIDDLE);
//    layer->setPosition(Point::ZERO);
    layer->setColor(Color3B::BLUE);
    layer->setOpacity(128);
    layer->setContentSize(Size(mapContentSizeW,
                               mapContentSizeH));
    layer->addChild(map);
    layer->addChild(mapObj);
    
    
    // レイヤーを包括するスクロールビューを定義（画面サイズで生成）
    scrollView = ScrollViewWrapper::create(visibleSize);
    scrollView->setDelegate(this);
    scrollView->setContentSize(Size(mapContentSizeW,
                                    mapContentSizeH));
//    scrollView->setInnerContainerSize(Size(map->getContentSize().width, map->getContentSize().height));
    scrollView->setContainer(layer);
//    scrollView->setAnchorPoint(Point::ZERO);
    scrollView->setPosition(Point(visibleSize.width * 3 / 100,
                                  visibleSize.height * 0 / 100));
    scrollView->setContentOffset(Point::ZERO);
    scrollView->setDirection(ScrollView::Direction::BOTH);
    scrollView->setBounceable(false);
    scrollView->setViewSize(Size(visibleSize.width,
                                 visibleSize.height));
    this->addChild(scrollView);
    
    initTouchEvent();
}

/**
 タッチイベントを初期化
 */
void SelectStoryScene::initTouchEvent()
{
    touchOn();
    
    // タッチエフェクト
    //    Sprite* effect = Sprite::createWithSpriteFrameName("touchEffect.png");
    //    touchEffectMotion = MotionStreak::create(1.0, 0.5f, 40.0f, Color3B(87,174,155), effect->getTexture());
    //    addChild(touchEffectMotion, ZOrder::TouchEffect);
}

/**
 *  タッチイベント有効化
 */
void SelectStoryScene::touchOn()
{
    //    listener = EventListenerTouchAllAtOnce::create();
    //    listener->onTouchesBegan = CC_CALLBACK_2(BattleScene::onTouchesBegan, this);
    //    listener->onTouchesMoved = CC_CALLBACK_2(BattleScene::onTouchesMoved, this);
    //    listener->onTouchesEnded = CC_CALLBACK_2(BattleScene::onTouchesEnded, this);
    //    listener->onTouchesCancelled = CC_CALLBACK_2(BattleScene::onTouchesCancelled, this);
    
    CCLOG("touchOn-start");
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(SelectStoryScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SelectStoryScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SelectStoryScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(SelectStoryScene::onTouchCancelled, this);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    CCLOG("touchOn-end");
}

/**
 *  タッチイベント無効化
 */
void SelectStoryScene::touchOff()
{
    this->getEventDispatcher()->removeEventListener(listener);
}

/**
 *  タッチ開始処理
 *
 *  @param touch   touch
 *  @param event   event
 */
bool SelectStoryScene::onTouchBegan(Touch* touch, Event *event){
    SoundManager* soundManager = new SoundManager();
    
    // タッチ位置
    auto location = touch->getLocation();

    Director* director = Director::getInstance();
    prevpos = director->convertToGL(touch->getLocationInView()); //get previous positon
    
    //    CCLOG("(onTouchesBegan) x:%f, y:%f", location.x, location.y);
    return true;
}

/**
 *  タッチ移動時処理
 *
 *  @param touch   touch
 *  @param event   event
 */
void SelectStoryScene::onTouchMoved(Touch* touch, Event *event){
    
    auto location = touch->getLocation();
    
    return;
}

/**
 *  タッチ終了時処理
 *
 *  @param touch   touch
 *  @param event   event
 */
void SelectStoryScene::onTouchEnded(Touch* touch, Event *event){
    
    auto location = touch->getLocation();
    
}

/**
 *  タッチキャンセル時処理
 *
 *  @param touch   touch
 *  @param event   event
 */
void SelectStoryScene::onTouchCancelled(Touch* touch, Event *event){
    
    auto location = touch->getLocation();
    
    //    CCLOG("(onTouchesEnded) x:%f, y:%f", location.x, location.y);
    
    return;
}

int SelectStoryScene::difference(int x,int y){ //差分計算
    return x>y?x-y:y-x;
}

//// スクロール
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
