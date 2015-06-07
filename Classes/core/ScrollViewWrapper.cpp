//
//  ScrollViewWrapper.cpp
//  mikumo-burst
//
//  Created by m.yamaoka on 2015/06/07.
//
//

#include "cocos-ext.h"
#include "ScrollViewWrapper.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

ScrollViewWrapper* ScrollViewWrapper::create(Size size, Node* container/* = nullptr*/)
{
    ScrollViewWrapper* pRet = new (std::nothrow) ScrollViewWrapper();
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

ScrollViewWrapper* ScrollViewWrapper::create()
{
    ScrollViewWrapper* pRet = new (std::nothrow) ScrollViewWrapper();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void ScrollViewWrapper::deaccelerateScrolling(float dt)
{
    if (_dragging)
    {
        this->unschedule(CC_SCHEDULE_SELECTOR(ScrollViewWrapper::deaccelerateScrolling));
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
        this->unschedule(CC_SCHEDULE_SELECTOR(ScrollViewWrapper::deaccelerateScrolling));
        this->relocateContainer(true);
    }
}

void ScrollViewWrapper::onTouchEnded(Touch* touch, Event* event)
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
            this->schedule(CC_SCHEDULE_SELECTOR(ScrollViewWrapper::deaccelerateScrolling));
        }
        _touches.erase(touchIter);
    }
    
    if (_touches.size() == 0)
    {
        _dragging = false;
        _touchMoved = false;
    }
}
