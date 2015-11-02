#include "scene/SelectStoryScene.h"
#include "scene/SelectSceneLoader.h"
#include "tools/GoogleAnalyticsTracker.h"
#include "core/Constant.h"
#include "core/GameManager.h"
#include "factory/CharacterCreator.h"
#include "resources/SoundManager.h"
#include "factory/TextCreator.h"
#include "core/ScrollMenu.h"
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
//    CC_SAFE_RELEASE_NULL(appsInfo);
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

    // ストーリー情報取得
    appsInfo = AppsInformation::create();
    appsInfo->scenarioCache->readCache();

    // ストーリー一覧
    this->setStoryList();
    
    // メニューボタン描画
    this->initMenu();

    // ゲーム開始前設定
    setupGame();
}

/**
 メニューボタン描画
 */
void SelectStoryScene::initMenu()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    float mapContentSizeW = visibleSize.width;
    float mapContentSizeH = visibleSize.height * 4.0f;
    
    // メニュー画像を包括するレイヤーを定義
    Layer *layer = LayerColor::create();
    layer->setContentSize(Size(mapContentSizeW,
                               mapContentSizeH));

    // メニュー作成
    Vector<MenuItem*> menuItems;
    
    // craete itemのラムダ関数作成
    function<MenuItemSprite* (std::string title, std::string subTitle, std::string description)> createMenuItemSprite =
    [this](std::string title, std::string subTitle, std::string description) {
        // メニュー項目背景を読み込む
        auto menuBgImage = SpriteBatchNode::create("avg2.png");
        // メニュー項目用スプライトを生成
        auto menuBgImageSpriteDefault = Sprite::createWithTexture(menuBgImage->getTexture());
        auto menuBgImageSpriteSelected = Sprite::createWithTexture(menuBgImage->getTexture());
        menuBgImageSpriteSelected->setColor(Color3B::BLACK);
        auto menuSprite = MenuItemSprite::create(menuBgImageSpriteDefault,
                                                 menuBgImageSpriteSelected,
                                                 CC_CALLBACK_1(SelectStoryScene::tapMenuItem, this));
        menuSprite->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
        // メニュー項目用文字列を生成
        Label* label;
        label = TextCreator::createLabel(title,
                                         Point(menuSprite->getContentSize().width * 4 / 100,
                                               menuSprite->getContentSize().height * 9 / 10));
        menuSprite->addChild(label);

        label = TextCreator::createLabel(subTitle,
                                         Point(menuSprite->getContentSize().width * 4 / 100,
                                               menuSprite->getContentSize().height * 6 / 10));
        menuSprite->addChild(label);

        label = TextCreator::createLabel(description,
                                         Point(menuSprite->getContentSize().width * 4 / 100,
                                               menuSprite->getContentSize().height * 4 / 10));
        menuSprite->addChild(label);

        return menuSprite;
    };
    
    int idx = 0;
    for (auto it = menuList.begin(); it != menuList.end(); it++)
    {
        StringMap column = (*it);
        
        //メニューアイテムの作成
        auto menuSprite = createMenuItemSprite(
                           column["menu_title"] + " " + column["menu_id"] + "-" + column["sub_id"],
                           column["sub_title"],
                           column["description"]);
//        auto menuItem2 = createMenuItemSprite("item 2");

        menuSprite->setPosition(Point(mapContentSizeW * 1 / 2,
                                      mapContentSizeH * (100 - 5 * idx) / 100));
        menuItems.pushBack(menuSprite);
        idx++;
//            //メニューの作成　pMenuの中にpBtnItemを入れる
//            auto pMenu = ScrollMenu::create(menuSprite, NULL);
//
//            //pMenuを画面中央に配置
//            pMenu->setPosition(Point(mapContentSizeW * 1 / 2,
//                                                (float((i1*3+3-i)+ofs)*15/100*visibleSize.height)));
//            layer->addChild(pMenu);
    }
    
    // ScrollMenuを作成
    auto menu = ScrollMenu::createWithArray(menuItems);
    menu->setContentSize(Size(mapContentSizeW,
                              mapContentSizeH));
    menu->setAnchorPoint(Vec2(0, 0));
    menu->setPosition(Vec2(0, 0));
    
    // レイヤーを包括するスクロールビューを定義（画面サイズで生成）
    ui::ScrollView* scrollView = ui::ScrollView::create();
    scrollView->setInnerContainerSize(Size(mapContentSizeW,
                                           mapContentSizeH));
    scrollView->setAnchorPoint(Point::ZERO);
    scrollView->setPosition(Point(visibleSize.width * 3 / 100,
                                  visibleSize.height * 0 / 100));
    scrollView->setContentSize(Size(visibleSize.width,
                                 visibleSize.height));
    scrollView->setScrollBarWidth(4);
    scrollView->setScrollBarPositionFromCorner(Vec2(2, 2));
    scrollView->setScrollBarColor(Color3B::WHITE);
    scrollView->addChild(menu);
    scrollView->setBounceEnabled(true);
    scrollView->setSwallowTouches(false);

    this->addChild(scrollView);
}

/**
 ストーリーリスト設定
 */
void SelectStoryScene::tapMenuItem(Ref* sender)
{
    CCLOG("タップしたあと");
    MenuItemSprite* menuSprite = static_cast<MenuItemSprite*>(sender);
    menuSprite->setColor(Color3B::BLUE);
}

/**
 ストーリーリスト設定
 */
void SelectStoryScene::setStoryList()
{
    menuList.clear();

    picojson::object& sheets = appsInfo->scenarioCache->loader->jsonResult.get<picojson::object>();
    picojson::array& sheetColumns = sheets[Constant::SHEET_NAME_STORY_MENU()].get<picojson::array>();
    for (picojson::array::iterator it = sheetColumns.begin(); it != sheetColumns.end(); it++)
    {
        StringMap menu;
        picojson::object& column = it->get<picojson::object>();
        menu["menu_id"] = std::to_string((int)column["menu_id"].get<double>());
        menu["menu_title"] = (std::string)column["menu_title"].get<std::string>();
        menu["sub_id"] = std::to_string((int)column["sub_id"].get<double>());
        menu["sub_title"] = (std::string)column["sub_title"].get<std::string>();
        menu["description"] = (std::string)column["description"].get<std::string>();
        menuList.push_back(menu);
    }
}

/**
 ゲーム開始前設定
 */
void SelectStoryScene::setupGame()
{
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
void SelectStoryScene::scrollViewDidScroll(ui::ScrollView *view)
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
