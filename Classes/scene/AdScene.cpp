#include "AdScene.h"
#include "AppCCloudPlugin.h"

USING_NS_CC;

#define MEDIA_KEY "10c2f04d6675d8b434e3bed3ba06aeabba5b796e"

const static float FONTSIZE = 30.f;
const static string FONTNAME = "Arial";

void MenuData::calcNextIndex(){
    const int size = this->captions.size();
    if(size > 0){
        this->index = (this->index + 1) % size;
    }
}
string MenuData::getCaptionText()
{
    if(this->captions.size() == 0){
        return "";
    }
    return this->captions[this->index];
    
}
int MenuData::getIndex()
{
    return this->index;
}
MenuData::MenuData():index(0)
{
}
void MenuData::pushCaption(const string& str)
{
    this->captions.push_back(str);
}
bool MenuData::init(){
    return true;
}
//-----------------------------
Scene* Ad::createScene()
{
    bool startResult = AppCCloudPlugin::setMK_iOS(MEDIA_KEY).start();
    if(startResult){
        CCLOG("start() succeeded");
    }else{
        CCLOG("start() failed");
    }
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Ad::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
/**
 *  MENU取得生成処理
 *
 *  @return メニューへのポインタ
 */
Menu* Ad::getMenu(){
    if(_pMenu == NULL){
        Size visibleSize = Director::getInstance()->getVisibleSize();
        _pMenu = Menu::create();
        _pMenu->setContentSize(visibleSize);
        _pMenu->setPosition(0.f, 0.f);
        
        this->addChild(_pMenu);
    }
    return _pMenu;
}
// on "init" you need to initialize your instance
bool Ad::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    _pMenu=NULL;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Ad::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Ad", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    // UI作成
    setSampleUI();
    
    return true;
}

/**
 *  閉じるボタンハンドラ
 *
 *  @param pSender sender
 */
void Ad::menuCloseCallback(Ref* pSender)
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
 *  MenuItemを返す
 *
 *  @param data  データ
 *  @param callbackコールバック
 *
 *  @return MenuItemLabel
 */
MenuItemLabel* Ad::createMenuItem(MenuData* data, const ccMenuCallback& callback){
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
 *  @return ラベル
 */
LabelTTF* Ad::createLabel(const string& text)
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
 *  サンプル用のUI追加処理
 */
void Ad::setSampleUI(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    Menu* pmenu = Menu::create();
    pmenu->setContentSize(visibleSize);
    pmenu->setPosition(0.f, 0.f);
    addChild(pmenu);
    
    MenuItemLabel* menuItem;
    
    float y[] = {
        origin.y+visibleSize.height * 9/12,
        origin.y+visibleSize.height * 8/12,
        origin.y+visibleSize.height * 7/12,
        origin.y+visibleSize.height * 6/12,
        origin.y+visibleSize.height * 5/12,
        origin.y+visibleSize.height * 4/12,
        origin.y+visibleSize.height * 3/12,
    } ;
    float x = origin.x+visibleSize.width / 2;
    // 全広告消去
    menuItem = createMenuCloseAll();
    menuItem->setPosition(x, y[0]);
    this->getMenu()->addChild(menuItem);
    
    // カットイン
    menuItem = createMenuCutin();
    menuItem->setPosition(x, y[1]);
    this->getMenu()->addChild(menuItem);
    
    // マーキー
    menuItem = createMenuMaquee();
    menuItem->setPosition(x, y[2]);
    this->getMenu()->addChild(menuItem);
    
    // 広告リスト型
    menuItem =createMenuList();
    menuItem->setPosition(x, y[3]);
    this->getMenu()->addChild(menuItem);
    
    // ムーブアイコン
    menuItem = createMenuMove();
    menuItem->setPosition(x, y[4]);
    this->getMenu()->addChild(menuItem);
    
    // シンプル型
    menuItem = createMenuSimple();
    menuItem->setPosition(x, y[5]);
    this->getMenu()->addChild(menuItem);
    
    // マッチアップバナー
    menuItem = createMenuMatchBanner();
    menuItem->setPosition(x, y[6]);
    this->getMenu()->addChild(menuItem);

    
//    float y[] = {3.f * visibleSize.height / 5.f, 2.f * visibleSize.height / 5.f, visibleSize.height / 5.f, } ;
//    float x[] = {visibleSize.width / 4.f - 40.f, 2.f * visibleSize.width / 4.f, 3.f * visibleSize.width / 4.f + 40.f,};
//    // 全広告消去
//    menuItem = createMenuCloseAll();
//    menuItem->setPosition(x[0], y[0]);
//    this->getMenu()->addChild(menuItem);
//    
//    // カットイン
//    menuItem = createMenuCutin();
//    menuItem->setPosition(x[0], y[1]);
//    this->getMenu()->addChild(menuItem);
//    
//    // マーキー
//    menuItem = createMenuMaquee();
//    menuItem->setPosition(x[0], y[2]);
//    this->getMenu()->addChild(menuItem);
//    
//    // 広告リスト型
//    menuItem =createMenuList();
//    menuItem->setPosition(x[1], y[0]);
//    this->getMenu()->addChild(menuItem);
//
//    // ムーブアイコン
//    menuItem = createMenuMove();
//    menuItem->setPosition(x[1], y[1]);
//    this->getMenu()->addChild(menuItem);
//    
//    // シンプル型
//    menuItem = createMenuSimple();
//    menuItem->setPosition(x[1], y[2]);
//    this->getMenu()->addChild(menuItem);
//    
//    // マッチアップバナー
//    menuItem = createMenuMatchBanner();
//    menuItem->setPosition(x[2], y[0]);
//    this->getMenu()->addChild(menuItem);
}

/**
 *  広告消去関連メニュー
 *
 *  @return メニュー
 */
MenuItemLabel* Ad::createMenuCloseAll()
{
    Ad &me = *this;
    auto menuData = MenuData::create();
    menuData = MenuData::create();
    menuData->pushCaption("全広告消去");
    auto menuItem = this->createMenuItem(menuData, [](Ref* sender){
        // 全広告消去
        AppCCloudPlugin::Ad::hideAllAdViews();
    });
    return menuItem;
}

/**
 *  広告リスト型関連メニュー
 *
 *  @return メニュー
 */
MenuItemLabel* Ad::createMenuList()
{
    Ad &me = *this;
    auto menuData = MenuData::create();
    menuData = MenuData::create();
    menuData->pushCaption("広告リスト型表示");
    auto menuItem = this->createMenuItem(menuData, [](Ref* sender){
        // 広告リスト型表示
        AppCCloudPlugin::Ad::openAdListView();
    });
    return menuItem;
}

/**
 *  カットイン関連メニュー
 *
 *  @return メニュー
 */
MenuItemLabel* Ad::createMenuCutin()
{
    Ad &me = *this;
    auto menuData = MenuData::create();
    menuData->pushCaption("カットイン");
    menuData->pushCaption("カットイン（アプリ終了）");
    auto menuItem = this->createMenuItem(menuData, [&me](Ref* sender){
        MenuItemLabel* miLabel = dynamic_cast<MenuItemLabel*>(sender);
        auto menuData = (MenuData*)miLabel->getUserData();
        if(menuData->getIndex()== 0){
            // カットイン表示
            AppCCloudPlugin::Ad::showCutin();
        }else{
            // カットイン（アプリ終了）表示
            // iOSでは無効
            AppCCloudPlugin::Ad::showCutinFinish();
        }
        menuData->calcNextIndex();
        miLabel->setLabel( me.createLabel(menuData->getCaptionText()) );
        
    });
    return menuItem;
}

/**
 *  マーキー関連メニュー
 *
 *  @return メニュー
 */
MenuItemLabel* Ad::createMenuMaquee()
{
    Ad &me = *this;
    auto menuData = MenuData::create();
    menuData->pushCaption("マーキー（上側）");
    menuData->pushCaption("マーキー消去");
    menuData->pushCaption("マーキー（下側）");
    menuData->pushCaption("マーキー消去");
    auto  menuItem = this->createMenuItem(menuData, [&me](Ref* sender){
        MenuItemLabel* miLabel = dynamic_cast<MenuItemLabel*>(sender);
        auto menuData = (MenuData*)miLabel->getUserData();
        int index = menuData->getIndex();
        switch(index){
            case 0:
                // マーキー表示（上側）
                AppCCloudPlugin::Ad::showMarqueeView(AppCCloudPlugin::TOP);
                break;
            case 2:
                // マーキー表示 (下側)
                AppCCloudPlugin::Ad::showMarqueeView(AppCCloudPlugin::BOTTOM);
                break;
            case 1:
            case 3:
                // マーキー消去
                AppCCloudPlugin::Ad::hideMarqueeView();
                break;
        }
        menuData->calcNextIndex();
        miLabel->setLabel( me.createLabel(menuData->getCaptionText()) );
    });
    return menuItem;
}

/**
 *  ムーブアイコン関連
 *
 *  @return ラベル
 */
MenuItemLabel* Ad::createMenuMove()
{
    Ad &me = *this;
    auto menuData = MenuData::create();
    menuData->pushCaption("ムーブアイコン（左上）");
    menuData->pushCaption("ムーブアイコン消去");
    menuData->pushCaption("ムーブアイコン（右上）");
    menuData->pushCaption("ムーブアイコン消去");
    menuData->pushCaption("ムーブアイコン（右下）");
    menuData->pushCaption("ムーブアイコン消去");
    menuData->pushCaption("ムーブアイコン（左下）");
    menuData->pushCaption("ムーブアイコン消去");
    auto menuItem = this->createMenuItem(menuData, [&me](Ref* sender){
        MenuItemLabel* miLabel = dynamic_cast<MenuItemLabel*>(sender);
        auto menuData = (MenuData*)miLabel->getUserData();
        int index = menuData->getIndex();
        switch(index){
            case 0:
                // ムーブアイコン表示（左上）
                AppCCloudPlugin::Ad::showMoveIconView(AppCCloudPlugin::LEFT, AppCCloudPlugin::TOP);
                break;
            case 2:
                // ムーブアイコン表示 (右上)
                AppCCloudPlugin::Ad::showMoveIconView(AppCCloudPlugin::RIGHT, AppCCloudPlugin::TOP);
                break;
            case 4:
                // ムーブアイコン表示 (右下)
                AppCCloudPlugin::Ad::showMoveIconView(AppCCloudPlugin::RIGHT, AppCCloudPlugin::BOTTOM);
                break;
            case 6:
                // ムーブアイコン表示 (左下)
                AppCCloudPlugin::Ad::showMoveIconView(AppCCloudPlugin::LEFT, AppCCloudPlugin::BOTTOM);
                break;
            case 1:
            case 3:
            case 5:
            case 7:
                // ムーブアイコン消去
                AppCCloudPlugin::Ad::hideMoveIconView();
                break;
        }
        menuData->calcNextIndex();
        miLabel->setLabel( me.createLabel(menuData->getCaptionText()) );
    });
    return menuItem;
}

/**
 *  シンプル関連メニュー
 *
 *  @return メニュー
 */
MenuItemLabel* Ad::createMenuSimple()
{
    Ad &me = *this;
    auto menuData = MenuData::create();
    menuData->pushCaption("シンプル（上側）");
    menuData->pushCaption("シンプル消去");
    menuData->pushCaption("シンプル（下側）");
    menuData->pushCaption("シンプル消去");
    auto menuItem = this->createMenuItem(menuData, [&me](Ref* sender){
        MenuItemLabel* miLabel = dynamic_cast<MenuItemLabel*>(sender);
        auto menuData = (MenuData*)miLabel->getUserData();
        int index = menuData->getIndex();
        switch(index){
            case 0:
                // シンプル表示（上側）
                AppCCloudPlugin::Ad::showSimpleView(AppCCloudPlugin::TOP);
                break;
            case 2:
                // シンプル表示 (下側)
                AppCCloudPlugin::Ad::showSimpleView(AppCCloudPlugin::BOTTOM);
                break;
            case 1:
            case 3:
                // シンプル消去
                AppCCloudPlugin::Ad::hideSimpleView();
                break;
        }
        menuData->calcNextIndex();
        miLabel->setLabel( me.createLabel(menuData->getCaptionText()) );
    });
    return menuItem;
}


/**
 *  マッチアップバナー関連メニュー
 *
 *  @return メニュー
 */
MenuItemLabel* Ad::createMenuMatchBanner()
{
    Ad &me = *this;
    auto menuData = MenuData::create();
    menuData->pushCaption("マッチアップバナー\n（左上）");
    menuData->pushCaption("マッチアップバナー\n消去");
    menuData->pushCaption("マッチアップバナー\n（右上）");
    menuData->pushCaption("マッチアップバナー\n消去");
    menuData->pushCaption("マッチアップバナー\n（右下）");
    menuData->pushCaption("マッチアップバナー\n消去");
    menuData->pushCaption("マッチアップバナー\n（左下）");
    menuData->pushCaption("マッチアップバナー\n消去");
    auto menuItem = this->createMenuItem(menuData, [&me](Ref* sender){
        MenuItemLabel* miLabel = dynamic_cast<MenuItemLabel*>(sender);
        auto menuData = (MenuData*)miLabel->getUserData();
        int index = menuData->getIndex();
        switch(index){
            case 0:
                // マッチアップバナー表示（左上）
                AppCCloudPlugin::Ad::showMatchAppView(AppCCloudPlugin::LEFT, AppCCloudPlugin::TOP);
                break;
            case 2:
                // マッチアップバナー表示 (右上)
                AppCCloudPlugin::Ad::showMatchAppView(AppCCloudPlugin::RIGHT, AppCCloudPlugin::TOP);
                break;
            case 4:
                // マッチアップバナー表示 (右下)
                AppCCloudPlugin::Ad::showMatchAppView(AppCCloudPlugin::RIGHT, AppCCloudPlugin::BOTTOM);
                break;
            case 6:
                // マッチアップバナー表示 (左下)
                AppCCloudPlugin::Ad::showMatchAppView(AppCCloudPlugin::LEFT, AppCCloudPlugin::BOTTOM);
                break;
            case 1:
            case 3:
            case 5:
            case 7:
                // マッチアップバナー消去
                AppCCloudPlugin::Ad::hideMatchAppView();
                break;
        }
        menuData->calcNextIndex();
        miLabel->setLabel( me.createLabel(menuData->getCaptionText()) );
        
    });
    return menuItem;
}




