#include "HomeScene.h"
#include "TitleScene.h"

USING_NS_CC;

Scene *Home::createScene()
{
    auto scene = Scene::create();
    auto layer = Home::create();
    scene->addChild(layer);
    return scene;
}


bool Home::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    //背景
    Sprite* background = Sprite::create("l_095.png");
    background->setPosition(Point(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2));
    this->addChild(background, 0);
    
    //戻るボタン
    auto backButton = MenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(Home::pushBack, this));
    
    backButton->setPosition(Point(origin.x + visibleSize.width - backButton->getContentSize().width / 2 ,
                                  origin.y + backButton->getContentSize().height / 2));
    
    //create menu, it's an autorelease object
    auto menu = Menu::create(backButton, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

void Home::pushBack(Ref *pSender)
{
//    Scene *pScene = Title::createScene();
//    
//    TransitionFade* transition = TransitionFade::create(0.5f, pScene);
//    Director::getInstance()->replaceScene(transition);
}

