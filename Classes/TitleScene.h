#ifndef __Positions__TitleScene__
#define __Positions__TitleScene__

#include "cocos2d.h"

class Title : public cocos2d::Layer
{
protected:
    enum Tag
    {
        MENU = 1,
        START_BUTTON,
    };
    void itemVibration();
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(Title);
    
    void pushStart(Ref* pSender);
};

#endif /* defined(__Positions__TitleScene__) */
