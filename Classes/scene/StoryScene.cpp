#include "scene/StoryScene.h"
#include "scene/SelectSceneLoader.h"
#include "tools/GoogleAnalyticsTracker.h"
#include "core/Constant.h"
#include "resources/SoundManager.h"
#include "factory/TextCreator.h"
#include "tools/NativeLauncher.h"
#include "core/LabelAttributedBMFont.h"

StoryScene::StoryScene()
: bgImageList(Constant::BG_IMAGE_LIST())
{
}

StoryScene::~StoryScene()
{
}

bool StoryScene::init()
{
//    GoogleAnalyticsTracker::sendScreen("StoryScene");
    if(!Layer::init())
    {
        return false;
    }
    
    initBackground();
    
    return true;
}

SEL_MenuHandler StoryScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    return NULL;
}

Control::Handler StoryScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBackButton", StoryScene::tappedBackButton);
    return NULL;
}

void StoryScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("character/persona2/persona2.plist");
    frameCache->addSpriteFramesWithFile("misc/misc.plist");

    // SE
    SoundManager* soundManager = new SoundManager();
    soundManager->preloadSE("se_select");

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // メニュー表示
    float labelWidth = origin.x + visibleSize.width / 2;
    float relativeLabelHeight = 40.0f;
    Point point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 100);
    Sprite* windowSprite = Sprite::createWithSpriteFrameName("menu_window.png");
    windowSprite->setPosition(point);
    windowSprite->setScale(windowSprite->getScale(),
                           windowSprite->getScale() * 40 / 100);
    addChild(windowSprite, ZOrder::Menu);
    
    // 表示文字準備
    LabelAttributedBMFont* label;
    Constant::StringVector pages;
    pages.push_back("あいうえおー\nかきくけこー");
    pages.push_back("さしすせそー");
    
    relativeLabelHeight = 4.0f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    label = TextCreator::create(pages, point);
    label->setScale(BM_FONT_SIZE64(16));
    this->addChild(label, ZOrder::Font);
    
    
    
    // 強調キーワードを設定する場合
    label->addKeyWord("おー", Color3B::RED);   // 強調キーワード, 強調色
    // 複数あるならもう繰り返し
    label->addKeyWord("すせー", Color3B::YELLOW);   // 強調キーワード, 強調色
    
    // コールバック設定するなら(全表示が終わったときにタップされると呼ばれる)
    label->setCallback([](Ref *sender){
        // 処理記述
        CCLOG("setCallback");
    });
    
    // コールバック設定その２(ページ送りするたびに呼ばれる)
    // もどってくる値はpagesのindex
    label->setCallbackChangedPage([](int index) {
        // indexから現在何が表示されているのか判定して何か処理
        // ページ送りされたらなので、indexは1から(2ページ目からしかこない)
        CCLOG("setCallbackChangedPage");
    });
    
    // 文字送りしない場合(ページ送りとキーワード強調は有効にしたい場合)
    // label->setDispSpeed(0);
    
    // 文字送り開始(これやんないと何も始まらないYo)
    label->start();
}

/**
 背景を初期化
 */
void StoryScene::initBackground()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    int num = arc4random() % bgImageList.size();
    Sprite* background = Sprite::createWithSpriteFrameName(StringUtils::format("%s.png", bgImageList.at(num).c_str()));
    background->setPosition(Point(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2));
    
    float scale = Director::getInstance()->getContentScaleFactor();
    background->setScale(background->getScale()*scale, background->getScale()*scale);
    
    this->addChild(background, ZOrder::Bg);
}

//void StoryScene::tappedBackButton(Ref* pTarget, Control::EventType pControlEventType)
//{
//    CCLOG("tappedBackButton eventType = %d", pControlEventType);
//    SoundManager* soundManager = new SoundManager();
//    soundManager->playSE("se_select");
//    
//    Scene* scene = SelectSceneLoader::createScene();
//    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
//    Director::getInstance()->replaceScene(trans);
//}
