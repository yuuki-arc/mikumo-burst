#ifndef __Fragment_of_Eternity__EffectManager__
#define __Fragment_of_Eternity__EffectManager__

#include "cocos2d.h"

USING_NS_CC;

class EffectManager
{
public:
    virtual bool init();
    
    Sprite* effectPurified(std::string effectName, int count, Point location);
    
};

#endif /* defined(__Fragment_of_Eternity__EffectManager__) */
