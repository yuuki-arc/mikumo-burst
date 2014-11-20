#ifndef __10sec_BURST__EffectManager__
#define __10sec_BURST__EffectManager__

#include "cocos2d.h"

USING_NS_CC;

class EffectManager
{
public:
    Sprite* effectPurified(std::string effectName, int count, Point location);
    
};

#endif /* defined(__10sec_BURST__EffectManager__) */
