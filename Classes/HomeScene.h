#ifndef __Positions__MenuScene__
#define __Positions__MenuScene__

#include "cocos2d.h"

class Home : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(Home);
    
    void pushBack(Ref* pSender);
};

#endif /* defined(__Positions__MenuScene__) */
