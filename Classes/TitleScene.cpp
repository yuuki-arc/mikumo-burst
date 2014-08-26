#include "TitleScene.h"
#include "HomeScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

Scene *Title::createScene()
{
    auto scene = Scene::create();
    auto layer = Title::create();
    scene->addChild(layer);
    return scene;
}


bool Title::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    srand((unsigned int)time(NULL));
    
    // BGM
    auto audioEngine = SimpleAudioEngine::getInstance();
    if (!audioEngine->isBackgroundMusicPlaying())
        audioEngine->playBackgroundMusic("game_maoudamashii_3_theme05.mp3", true);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // 背景
    Sprite* background = Sprite::create("l_095.png");
    background->setPosition(Point(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2));
    this->addChild(background, 0);
    
    // タイトル
    Sprite* logo = Sprite::create("title_logo.png");
    logo->setPosition(Point(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - 100));
    this->addChild(logo, 1);

    // メニュー
    function<MenuItem* (const char *text, float x, float y)> createMenuItem =
    [](const char *text, float x, float y) {
        auto normal = Label::createWithSystemFont(text, "Impact", 32);
        normal->setPosition(Point(x, y));
        auto selected = Label::createWithSystemFont(text, "Impact", 32);
        selected->setColor(Color3B::GRAY);
        selected->setPosition(Point(x, y));
        return MenuItemSprite::create(normal, selected);
    };
    
    auto menuItem1 = createMenuItem("START",
                                    origin.x + visibleSize.width / 2,
                                    origin.y + visibleSize.height - 120);
    auto menuItem2 = createMenuItem("SETTINGS",
                                    origin.x + visibleSize.width / 2,
                                    origin.y + visibleSize.height - 140);
    auto menu = Menu::create(menuItem1, menuItem2, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    // メニュー
    auto lbl_title = LabelTTF::create("copyright(c) 2014", "HiraKakuProN-W6", 16);
    lbl_title->setPosition(Point(origin.x + visibleSize.width / 2,
                                 origin.y + lbl_title->getContentSize().height));
    this->addChild(lbl_title,1);
    
    return true;
}

void Title::pushStart(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ComedyWhistle.caf");
    
    Scene *pScene = Home::createScene();
    TransitionFade* transition = TransitionFade::create(0.5f, pScene);
    Director::getInstance()->replaceScene(transition);
}
