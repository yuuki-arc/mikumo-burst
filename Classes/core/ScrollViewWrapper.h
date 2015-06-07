//
//  ScrollViewWrapper.h
//  mikumo-burst
//
//  Created by m.yamaoka on 2015/06/07.
//
//

#ifndef __mikumo_burst__ScrollViewWrapper__
#define __mikumo_burst__ScrollViewWrapper__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define SCROLL_DEACCEL_RATE  0.95f
#define SCROLL_DEACCEL_DIST  1.0f
#define BOUNCE_DURATION      0.15f
#define INSET_RATIO          0.2f
#define MOVE_INCH            7.0f/160.0f
#define BOUNCE_BACK_FACTOR   0.35f

class ScrollViewWrapper : public ScrollView
{
    
public:
    static ScrollViewWrapper* create(Size size, Node* container = NULL);
    static ScrollViewWrapper* create();
    void onTouchEnded(Touch *touch, Event *event);
    
private:
    void deaccelerateScrolling(float dt);
};

#endif /* defined(__mikumo_burst__ScrollViewWrapper__) */
