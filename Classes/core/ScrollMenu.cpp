#include "ScrollMenu.h"

USING_NS_CC;

ScrollMenu::ScrollMenu() : Menu() {
    
}

ScrollMenu* ScrollMenu::createWithArray(const Vector<MenuItem*>& arrayOfItems)
{
    auto ret = new (std::nothrow) ScrollMenu();
    if (ret && ret->initWithArray(arrayOfItems))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

/**
 * 基本的にはcocos2d::Menu::initWithArrayと同様の処理
 * EventListenerTouchOneByOne->setSwallowTouchesのみ変更
 */
bool ScrollMenu::initWithArray(const Vector<MenuItem*>& arrayOfItems)
{
    if (Layer::init())
    {
        _enabled = true;
        // menu in the center of the screen
        Size s = Director::getInstance()->getWinSize();
        
        this->ignoreAnchorPointForPosition(true);
        setAnchorPoint(Vec2(0.5f, 0.5f));
        this->setContentSize(s);
        
        setPosition(s.width/2, s.height/2);
        
        int z=0;
        
        for (auto& item : arrayOfItems)
        {
            this->addChild(item, z);
            z++;
        }
        
        _selectedItem = nullptr;
        _state = Menu::State::WAITING;
        
        // enable cascade color and opacity on menus
        setCascadeColorEnabled(true);
        setCascadeOpacityEnabled(true);
        
        
        auto touchListener = EventListenerTouchOneByOne::create();
        /* 下のNodeへもタッチイベントを透過させる */
        //        touchListener->setSwallowTouches(true);
        touchListener->setSwallowTouches(false);
        
        touchListener->onTouchBegan = CC_CALLBACK_2(Menu::onTouchBegan, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(Menu::onTouchMoved, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(Menu::onTouchEnded, this);
        touchListener->onTouchCancelled = CC_CALLBACK_2(Menu::onTouchCancelled, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        
        return true;
    }
    return false;
}

void ScrollMenu::setMenuInMoving() {
    this->_inMoving = true;
}

bool ScrollMenu::onTouchBegan(Touch* touch, Event* event) {
    // タッチ開始時に，スクロール中フラグをfalseへセットする
    this->_inMoving = false;
    return Menu::onTouchBegan(touch, event);
}

void ScrollMenu::onTouchEnded(Touch *touch, Event *event) {
    // スクロール中だった場合はイベントをキャンセル，そうでなければ通常の終了処理
    if(this->_inMoving) {
        Menu::onTouchCancelled(touch, event);
    } else {
        Menu::onTouchEnded(touch, event);
    }
}