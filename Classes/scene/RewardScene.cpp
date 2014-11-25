//
// RewardScene.cpp
//
// appC cloud Plugin Cocos2d-x example
// Created by cayto inc.
//


#include "RewardScene.h"
#include "AppCCloudPlugin.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

#define MEDIA_KEY "fcdc2faa6825f93be079093c5d25c244533d437a"

// フォントサイズ
const static float FONTSIZE = 30.f;
// フォント名
const static string FONTNAME = "Arial";
const string Reward::SERVICEID_01 = "REWARD_SERVICE_ID01";


//-----------------------------

/**
 *  次のindexの計算
 */
void MenuData::calcNextIndex(){
    const size_t size = this->captions.size();
    if(size > 0){
        this->index = (this->index + 1) % size;
    }
}

/**
 *  文字列取得
 *
 *  @return 文字列
 */
string MenuData::getCaptionText()
{
    if(this->captions.size() == 0){
        return "";
    }
    return this->captions[this->index];
    
}

/**
 *  index取得
 *
 *  @return index
 */
int MenuData::getIndex()
{
    return this->index;
}

/**
 *  コンストラクタ
 */
MenuData::MenuData():index(0)
{
}

/**
 *  文字列追加
 *
 *  @param str 文字列
 */
void MenuData::pushCaption(const string& str)
{
    this->captions.push_back(str);
}

/**
 *  初期化処理
 *
 *  @return true:
 */
bool MenuData::init(){
    return true;
}
//-----------------------------



/**
 *  scene作成
 *
 *  @return scene
 */
Scene*  Reward::createScene()
{
    bool startResult = AppCCloudPlugin::setOptions(API_PURCHASE|API_REWARD).setMK_iOS(MEDIA_KEY).start();
    if(startResult){
        CCLOG("start() succeeded");
    }else{
        CCLOG("start() failed");
    }
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer =  Reward::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

/**
 *  initialize instance
 *
 *  @return true: sucess
 */
bool  Reward::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1( Reward::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2.f ,
                                origin.y + closeItem->getContentSize().height / 2.f));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Reward", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2.f,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);


    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width / 2.f + origin.x, visibleSize.height / 2.f + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    setSampleUI();
    
    return true;
}

/**
 *  閉じるボタンのコールバック
 *
 *  @param pSender sender
 */
void  Reward::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


/**
 *  UI設定
 */
void Reward::setSampleUI()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Size buttonSize{400.f, 50.f};

    const float yTmp = visibleSize.height - 80.f;
    float x = origin.x + visibleSize.width / 2.f;
    float btnx = x;
    float tmpx;
    
    float y = yTmp - 100.f;
    // 自サービス01画面表示ボタン
    auto menuItemDisplayService = this->createMenuItemDisplayService();
    menuItemDisplayService->setPosition(Vec2(btnx, y) );
    this->getMenu()->addChild(menuItemDisplayService);
    
    y -= menuItemDisplayService->getContentSize().height + 10.f;
    
    // ポイント画面表示ボタン
    auto menuItemDisplayPointService = this->createMenuItemDisplayPointService();
    menuItemDisplayPointService->setPosition(Vec2(x, y));
    this->getMenu()->addChild(menuItemDisplayPointService);
    
    y -= menuItemDisplayPointService->getContentSize().height + 10.f;

    // 自サービス状態の更新
    auto menuItemReloadStatus = this->createMenuItemReloadServiceStatus();
    menuItemReloadStatus->setPosition(Vec2(x, y));
    this->getMenu()->addChild(menuItemReloadStatus);

    y -= menuItemReloadStatus->getContentSize().height + 10.f;

    // 自サービス状態リセット
    auto menuItemResetStatus = this->createMenuItemResetServiceStatus();
    menuItemResetStatus->setPosition(Vec2(x, y));
    this->getMenu()->addChild(menuItemResetStatus);
    
    y -= menuItemResetStatus->getContentSize().height * 2.f;
    // 状態を表示するためのラベル
    auto labelTitleS1 = LabelTTF::create("自サービス01　状態", FONTNAME, FONTSIZE);

    labelTitleS1->setPosition(Vec2(x, y));
    labelTitleS1->enableStroke(Color3B::BLACK, 5.f);
    labelTitleS1->setFontFillColor(Color3B::WHITE);
    this->addChild(labelTitleS1);

    _labelStatusS1 = LabelTTF::create("OFF", FONTNAME, FONTSIZE);
    tmpx = x + labelTitleS1->getContentSize().width + 5.f;
    _labelStatusS1->setPosition(Vec2(tmpx, y));
    _labelStatusS1->enableStroke(Color3B::BLACK, 5.f);
    _labelStatusS1->setFontFillColor(Color3B::WHITE);
    this->addChild(_labelStatusS1);

    viewInfo();
}
/**
 *  状態を読んで、ラベルに表示する。
 */
void Reward::viewInfo() {
    // 状態読み込み
    bool serviceId01flg = AppCCloudPlugin::Reward::isRewardService(Reward::SERVICEID_01);
    // ラベルに設定
    _labelStatusS1->setString(serviceId01flg ? "ON" : "OFF");
}

/**
 *  自サービス状態リセットメニュー作成
 *
 *  @return メニューアイテム
 */
MenuItemLabel* Reward::createMenuItemResetServiceStatus()
{
    Reward &me = *this;
    auto data = MenuData::create();
    data->pushCaption("自サービス状態リセット");
    auto menuItem = createMenuItem(data, [&me](Ref* sender){
        // 状態リセット
        AppCCloudPlugin::Reward::rewardClearService(Reward::SERVICEID_01);
        
        // 状態を取得して表示
        me.viewInfo();
    });
    return menuItem;
}

/**
 *  自サービス状態再取得メニュー作成
 *
 *  @return メニューアイテム
 */
MenuItemLabel* Reward::createMenuItemReloadServiceStatus()
{
    Reward &me = *this;
    auto data = MenuData::create();
    data->pushCaption("自サービス状態再取得");
    auto menuItem = createMenuItem(data, [&me](Ref* sender){
        // 状態リセット
        AppCCloudPlugin::Reward::rewardClearService(Reward::SERVICEID_01);
        
        // 状態を取得して表示
        me.viewInfo();
    });
    return menuItem;
}

/**
 *  自サービス画面表示
 *
 *  @return メニューアイテム
 */
MenuItemLabel* Reward::createMenuItemDisplayService()
{
    Reward &me = *this;
    auto data = MenuData::create();
    data->pushCaption("自サービス画面表示");
    auto menuItem = createMenuItem(data, [&me](Ref* sender){
        // 自サービス画面表示
        AppCCloudPlugin::Reward::openRewardServiceViews(Reward::SERVICEID_01);
        // 状態を取得して表示
        me.viewInfo();
    });
    return menuItem;
}

/**
 *  ポイント画面表示メニュー作成
 *
 *  @return メニュー
 */
MenuItemLabel* Reward::createMenuItemDisplayPointService()
{
    Reward &me = *this;
    auto data = MenuData::create();
    data->pushCaption("ポイント画面表示");
    auto menuItem = createMenuItem(data, [&me](Ref* sender){
        //　ポイント画面表示処理
        AppCCloudPlugin::Reward::openRewardPointView();
        // 状態を取得して表示
        me.viewInfo();
    });
    return menuItem;
}

/**
 *  MenuItem作成
 *
 *  @param data  データ
 *  @param callbackコールバック
 *
 *  @return MenuItemLabel
 */
MenuItemLabel* Reward::createMenuItem(MenuData* data, const ccMenuCallback& callback){
    auto label = createLabel(data->getCaptionText());
    
    auto ret = MenuItemLabel::create(label, callback);
    data->retain();
    ret->setUserData( data );
    return ret;
}

/**
 *  ラベル作成
 *
 *  @param text 文字列
 *
 *  @return return value description
 */
LabelTTF* Reward::createLabel(const string& text)
{
    auto label = LabelTTF::create();
    label->setFontName(FONTNAME);
    label->setFontSize(FONTSIZE);
    label->enableStroke(Color3B::WHITE, 5.f);
    label->setFontFillColor(Color3B::BLUE);
    label->setString(text);
    
    return label;
}

/**
 *  MENU取得処理
 *
 *  @return メニューへのポインタ
 */
Menu* Reward::getMenu(){
    if(_pMenu == NULL){
        Size visibleSize = Director::getInstance()->getVisibleSize();
        _pMenu = Menu::create();
        _pMenu->setContentSize(visibleSize);
        _pMenu->setPosition(0.f, 0.f);
        
        this->addChild(_pMenu);
    }
    return _pMenu;
}
