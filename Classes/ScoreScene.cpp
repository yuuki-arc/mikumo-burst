#include "ScoreScene.h"
#include "SelectSceneLoader.h"
#include "Constant.h"
#include "SoundManager.h"
#include "TextCreator.h"
#include "UserDataStore.h"
#include "AppCCloudPlugin.h"
#include <iomanip>

ScoreScene::ScoreScene()
{
}

ScoreScene::~ScoreScene()
{
}

bool ScoreScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    return true;
}

SEL_MenuHandler ScoreScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    return NULL;
}

Control::Handler ScoreScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedScoreButton", ScoreScene::tappedScoreButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBackButton", ScoreScene::tappedBackButton);
    return NULL;
}

void ScoreScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // BGM
    SoundManager* soundManager = new SoundManager();
    soundManager->playBGM("bgm_title", true);
    
    // SE
    soundManager->preloadSE("se_select");

    //---------------------------------------------
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(ScoreScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2.f ,
                                origin.y + closeItem->getContentSize().height / 2.f));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    // create and initialize a label
    
    auto label = LabelTTF::create("Gamers", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2.f,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//    
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width / 2.f + origin.x, visibleSize.height / 2.f + origin.y));
//    
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
//    
    setSampleUI();
    
//    // スコア表示
//    float labelWidth = origin.x + visibleSize.width * 1 / 10;
//    float relativeLabelHeight;
//    Label* resultLabel;
//    Point point;
//    
//    const std::string KEY_RANK = Constant::UserDefaultKey::SCORE_TABLE_RANK();
//    const std::string KEY_SCORE = Constant::UserDefaultKey::SCORE_TABLE_SCORE();
//    const std::string KEY_BREAK = Constant::UserDefaultKey::SCORE_TABLE_BREAK();
//    
//    StringMapVector scoreList = UserDataStore::getInstance()->getScoreTable();
//    for (StringMapVector::iterator it = scoreList.begin(); it != scoreList.end(); it++)
//    {
//        StringMap map = (*it);
//        
//        labelWidth = origin.x + visibleSize.width * 2 / 10;
//        
//        relativeLabelHeight -= .6f;
//        point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
//        resultLabel = TextCreator::create("HIGH RANK: " + map[KEY_RANK], point);
//        this->addChild(resultLabel, ZOrder::Font);
//        
//        relativeLabelHeight -= .4f;
//        point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
//        resultLabel = TextCreator::create("TOTAL SCORE: " + map[KEY_SCORE], point);
//        this->addChild(resultLabel, ZOrder::Font);
//        
//        relativeLabelHeight -= .4f;
//        point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
//        resultLabel = TextCreator::create("TOTAL BREAK: " + map[KEY_BREAK], point);
//        this->addChild(resultLabel, ZOrder::Font);
//    }
}

void ScoreScene::tappedScoreButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedScoreButton eventType = %d", pControlEventType);
}

void ScoreScene::tappedBackButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedBackButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    
    Scene* scene = SelectSceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}

const static float FONTSIZE = 30.f;
const static string FONTNAME = "Arial";

//-----------------------------

/**
 *  次のindex取得
 */
void MenuData::calcNextIndex(){
    const int size = (int)this->captions.size();
    if(size > 0){
        this->index = (this->index + 1) % size;
    }
}
/**
 *  キャプションを返す
 *
 *  @return キャプション
 */
string MenuData::getCaptionText()
{
    if(this->captions.size() == 0){
        return "";
    }
    return this->captions[this->index];
}
/**
 *  indexを取得
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
 *  キャプション追加
 *
 *  @param str キャプション
 */
void MenuData::pushCaption(const string& str)
{
    this->captions.push_back(str);
}
/**
 *  キャプション
 *
 *  @return tru
 */
bool MenuData::init(){
    return true;
}
//-----------------------------

/**
 *  閉じるボタンハンドラ
 *
 *  @param pSender sender
 */
void ScoreScene::menuCloseCallback(Ref* pSender)
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
 *  サンプル用のUI追加処理
 */
void ScoreScene::setSampleUI(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    const float baseHeight = visibleSize.height - 200;
    vector<float> posY = {baseHeight - 60 ,  baseHeight - 140, baseHeight - 220,
        baseHeight - 300 , baseHeight - 380 };
    vector<float> posX = {visibleSize.width / 4.f, 3.f * visibleSize.width / 4.f};
    ssize_t num;
    // size of edit box
    Size editBoxSize(300, 60);
    
    Vector<Node*> nodesWrite;
    
    // 数値(int)
    // label
    auto labelInt = LabelTTF::create("High score int", FONTNAME, FONTSIZE * 1.2f);
    labelInt->enableStroke(Color3B::BLACK, 1.f);
    labelInt->setFontFillColor(Color3B::WHITE);
    
    // editbox
    _editBoxInt = EditBox::create(editBoxSize, Scale9Sprite::create("editbox.png"));
    _editBoxInt->setInputMode(EditBox::InputMode::NUMERIC);
    _editBoxInt->setFontColor(Color3B::BLACK);
    _editBoxInt->setFontSize(FONTSIZE);
    
    // int書き込みボタン
    auto menuWriteInt = createWriteIntMenu();
    this->getMenu()->addChild(menuWriteInt);
    
    // 数値(float)
    // label
    //auto labelFloat =createLabel("High score float").
    auto labelFloat = LabelTTF::create("High score float", FONTNAME, FONTSIZE * 1.2f);
    labelFloat->enableStroke(Color3B::BLACK, 1.f);
    labelFloat->setFontFillColor(Color3B::WHITE);
    
    // 数値editbox
    _editBoxFloat = EditBox::create(editBoxSize, Scale9Sprite::create("editbox.png"));
    _editBoxFloat->setInputMode(EditBox::InputMode::DECIMAL);
    _editBoxFloat->setFontColor(Color3B::BLACK);
    _editBoxFloat->setFontSize(FONTSIZE);
    
    // float書き込みメニュー
    auto menuWriteFloat = createWriteFloatMenu();
    this->getMenu()->addChild(menuWriteFloat);
    nodesWrite.pushBack(labelInt);
    nodesWrite.pushBack(_editBoxInt);
    nodesWrite.pushBack(menuWriteInt);
    nodesWrite.pushBack(labelFloat);
    nodesWrite.pushBack(_editBoxFloat);
    nodesWrite.pushBack(menuWriteFloat);
    
    Point topOfWrite(visibleSize.width / 4.f, visibleSize.height - 100.f);
    AlignVertical(nodesWrite, topOfWrite, 10.f);
    
    num = nodesWrite.size();
    for(ssize_t i =0 ; i < num; i++){
        if(nodesWrite.at(i) == menuWriteInt || nodesWrite.at(i) == menuWriteFloat)
        {
            continue;
        }
        addChild(nodesWrite.at(i));
    }
    Vector<Node*> nodesRead;
    
    // GameCenter表示
    auto menuOpenGamers = createOpenGameMenu();
    this->getMenu()->addChild(menuOpenGamers);
    
    
    // int　読み込みmenu
    auto menuReadInt = createReadIntMenu();
    this->getMenu()->addChild(menuReadInt);
    
    // labels for result
    _labelInt = LabelTTF::create(" ", FONTNAME, FONTSIZE);
    _labelInt->enableStroke(Color3B::RED, 1.f);
    _labelInt->setFontFillColor(Color3B::WHITE);
    
    // float　読み込みmenu
    auto menuReadFloat = createReadFloatMenu();
    this->getMenu()->addChild(menuReadFloat);
    
    // labels for result
    _labelFloat = LabelTTF::create(" ", FONTNAME, FONTSIZE);
    _labelFloat->enableStroke(Color3B::RED, 1.f);
    _labelFloat->setFontFillColor(Color3B::WHITE);
    
    nodesRead.pushBack(menuOpenGamers);
    nodesRead.pushBack(menuReadInt);
    nodesRead.pushBack(_labelInt);
    nodesRead.pushBack(menuReadFloat);
    nodesRead.pushBack(_labelFloat);
    
    Point topOfRead(3.f * visibleSize.width / 4.f, baseHeight - 30);
    AlignVertical(nodesRead, topOfRead, 30.f);
    
    num = nodesRead.size();
    for(ssize_t i =0 ; i < num; i++){
        if(nodesRead.at(i) == menuReadInt || nodesRead.at(i) == menuReadFloat || nodesRead.at(i) == menuOpenGamers)
        {
            continue;
        }
        addChild(nodesRead.at(i));
    }
    
    readIntFromLB();
    readFloatFromLB();
}

/**
 *  lbから値を読んで、ラベルに反映させる。（int）
 */
void ScoreScene::readIntFromLB(){
    // リーダーボードから値を取得
    LeaderBoardData data = AppCCloudPlugin::Gamers::getLeaderBoard(LEADERBOARD_INT);
    // 表示
    std::ostringstream strStream;
    strStream << data.getScore();
    string tmp = strStream.str();
    CCLOG("float=%f",data.getTime());
    CCLOG("int=%d",data.getScore());
    _labelInt->setString(tmp);
}

/**
 *  lbから値を読んで、ラベルに反映させる。（float）
 */
void ScoreScene::readFloatFromLB(){
    // リーダーボードから値を取得
    LeaderBoardData data = AppCCloudPlugin::Gamers::getLeaderBoard(LEADERBOARD_FLOAT);
    // 表示
    std::ostringstream strStream;
    strStream << left << data.getTime();
    string tmp = strStream.str();
    CCLOG("float=%f",data.getTime());
    CCLOG("int=%d",data.getScore());
    _labelFloat->setString(tmp);
    
}

/**
 *  MenuItemを返す
 *
 *  @param data  データ
 *  @param callbackコールバック
 *
 *  @return MenuItemLabel
 */
MenuItemLabel* ScoreScene::createMenuItem(MenuData* data, const ccMenuCallback& callback){
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
LabelTTF* ScoreScene::createLabel(const string& text)
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
 *  MENU取得生成処理
 *
 *  @return メニューへのポインタ
 */
Menu* ScoreScene::getMenu(){
    if(_pMenu == NULL){
        Size visibleSize = Director::getInstance()->getVisibleSize();
        _pMenu = Menu::create();
        _pMenu->setContentSize(visibleSize);
        _pMenu->setPosition(0.f, 0.f);
        this->addChild(_pMenu);
    }
    return _pMenu;
}

/**
 *  ゲーマー画面を開く
 *
 *  @return
 */
MenuItemLabel* ScoreScene::createOpenGameMenu()
{
    auto menudata = MenuData::create();
    menudata->pushCaption("Open gamers");
    auto menuItem = createMenuItem(menudata,[](Ref* ref){
        // GAMERS画面を開く
        AppCCloudPlugin::Gamers::showGamersView();
    });
    return menuItem;
}


/**
 *  整数書き込みメニュー作成
 *
 *  @return メニュー
 */
MenuItemLabel* ScoreScene::createWriteIntMenu()
{
    ScoreScene &me = *this;
    auto menudata = MenuData::create();
    menudata->pushCaption("Write int");
    auto menuItem = createMenuItem(menudata,[&me](Ref* ref){
        const char* text = me._editBoxInt->getText();
        // leader boardに書き込み
        AppCCloudPlugin::Gamers::setLeaderBoard(LEADERBOARD_INT, atoi(text));
        
    });
    return menuItem;
}
/**
 *  整数読み込みメニュー作成
 *
 *  @return メニュー
 */
MenuItemLabel* ScoreScene::createReadIntMenu()
{
    ScoreScene &me = *this;
    
    auto menudata = MenuData::create();
    menudata->pushCaption("Read int");
    
    auto menuItem = createMenuItem(menudata,[&me](Ref* ref){
        // leader boardから値を取得して表示
        me.readIntFromLB();
        
    });
    return menuItem;
}
/**
 *  少数書き込みメニュー作成
 *
 *  @return メニュー
 */
MenuItemLabel* ScoreScene::createWriteFloatMenu()
{
    ScoreScene&me = *this;
    auto menudata = MenuData::create();
    menudata->pushCaption("Write float");
    auto menuItem = createMenuItem(menudata,[&me](Ref* ref){
        const char* text = me._editBoxFloat->getText();
        // leader boardに書き込み
        AppCCloudPlugin::Gamers::setLeaderBoard(LEADERBOARD_FLOAT, (float)atof(text));
    });
    return menuItem;
}
/**
 *  少数読み込みメニュー作成
 *
 *  @return メニュー
 */
MenuItemLabel* ScoreScene::createReadFloatMenu()
{
    ScoreScene &me = *this;
    auto menudata = MenuData::create();
    menudata->pushCaption("Read float");
    auto menuItem = createMenuItem(menudata,[&me](Ref* ref){
        // leader boardから値を取得して表示
        me.readFloatFromLB();
    });
    return menuItem;
}
/**
 *  上から下へならべる
 *
 *  @param nodes  node
 *  @param topm   top positon
 *  @param margin margin betweeen nodes
 */
void ScoreScene::AlignVertical(cocos2d::Vector<cocos2d::Node*>& nodes, const Point& top,float margin)
{
    const ssize_t num = nodes.size();
    float x = top.x;
    float y = top.y;
    for(ssize_t i =0 ; i < num; i++){
        nodes.at(i)->setPosition(x,y);
        y -= nodes.at(i)->getContentSize().height + margin;
    }
}

