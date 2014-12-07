#ifndef __mikumoburst__EffectManager__
#define __mikumoburst__EffectManager__

#include "cocos2d.h"

USING_NS_CC;

class EffectManager
{
public:
    Sprite* effectPurified(std::string effectName, Point location, float scale, float delay = 0.1f);
    Sprite* effectPurifiedTwice(std::string effectName, Point location, float scale, float delay = 0.1f);
private:
    Animate* createFrameAnimation(std::string effectName, Point location, float scale, float delay = 0.1f);
};

#endif /* defined(__mikumoburst__EffectManager__) */
