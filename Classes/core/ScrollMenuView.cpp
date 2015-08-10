#include "ScrollMenuView.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define SCROLL_DEACCEL_RATE  0.95f
#define SCROLL_DEACCEL_DIST  1.0f
#define BOUNCE_DURATION      0.15f
#define INSET_RATIO          0.2f
#define MOVE_INCH            7.0f/160.0f
#define BOUNCE_BACK_FACTOR   0.35f

ScrollMenuView::ScrollMenuView() : ScrollView() {
}
ScrollMenuView::~ScrollMenuView() {
    CC_SAFE_RELEASE_NULL(_scrollMenu);
}

void ScrollMenuView::deaccelerateScrolling(float dt)
{
    if (_dragging)
    {
        this->unschedule(CC_SCHEDULE_SELECTOR(ScrollMenuView::deaccelerateScrolling));
        return;
    }
    
    float newX, newY;
    Vec2 maxInset, minInset;
    
    _container->setPosition(_container->getPosition() + _scrollDistance);
    
    if (_bounceable)
    {
        maxInset = _maxInset;
        minInset = _minInset;
    }
    else
    {
        maxInset = this->maxContainerOffset();
        minInset = this->minContainerOffset();
    }
    
    newX = _container->getPosition().x;
    newY = _container->getPosition().y;
    
    _scrollDistance     = _scrollDistance * SCROLL_DEACCEL_RATE;
    this->setContentOffset(Vec2(newX,newY));
    
    if ((fabsf(_scrollDistance.x) <= SCROLL_DEACCEL_DIST &&
         fabsf(_scrollDistance.y) <= SCROLL_DEACCEL_DIST) ||
        (_direction != Direction::HORIZONTAL && (newY >= maxInset.y || newY <= minInset.y)) ||
        (_direction != Direction::VERTICAL && (newX >= maxInset.x || newX <= minInset.x)))
    {
        this->unschedule(CC_SCHEDULE_SELECTOR(ScrollMenuView::deaccelerateScrolling));
        this->relocateContainer(true);
    }
}

ScrollMenuView* ScrollMenuView::create(Size size, Node* container/* = nullptr*/)
{
    ScrollMenuView* pRet = new (std::nothrow) ScrollMenuView();
    if (pRet && pRet->initWithViewSize(size, container))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

ScrollMenuView* ScrollMenuView::create()
{
    ScrollMenuView* pRet = new (std::nothrow) ScrollMenuView();
    if (pRet && ((ScrollView*)pRet)->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

ScrollMenuView* ScrollMenuView::create(ScrollMenu *menu) {
    ScrollMenuView* pRet = new (std::nothrow) ScrollMenuView();
    if (pRet && pRet->init(menu))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ScrollMenuView::init(ScrollMenu *menu) {
    if(!ScrollView::init()) {
        return false;
    }
    
    this->_scrollMenu = menu;
    this->addChild(menu, 1);
    
    return true;
}

bool ScrollMenuView::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    // タッチ開始時の座標を取得しておく
    this->_touchStartPoint = touch->getLocationInView();
    return ScrollView::onTouchBegan(touch, unusedEvent);
}

void ScrollMenuView::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent) {
    /*
     * タッチ開始時からの5.0f以上となった場合，子Nodeにセットしたメニューのスクロール中フラグを立てる
     * メニューをタップするだけのつもりでも多少タッチが移動してしまう場合を考慮し，
     * 5.0f以下の距離の移動ではメニューを有効とする
     */
    if(5.0f < touch->getLocationInView().distance(this->_touchStartPoint)) {
        this->_scrollMenu->setMenuInMoving();
    }
    ScrollView::onTouchMoved(touch, unusedEvent);
}

void ScrollMenuView::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    if (!this->isVisible())
    {
        return;
    }
    
    auto touchIter = std::find(_touches.begin(), _touches.end(), touch);
    
    if (touchIter != _touches.end())
    {
        if (_touches.size() == 1 && _touchMoved)
        {
            this->schedule(CC_SCHEDULE_SELECTOR(ScrollMenuView::deaccelerateScrolling));
        }
        _touches.erase(touchIter);
    }
    
    if (_touches.size() == 0)
    {
        _dragging = false;
        _touchMoved = false;
    }
}
