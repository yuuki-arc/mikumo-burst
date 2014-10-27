#ifndef __Fragment_of_Eternity__TextCreator__
#define __Fragment_of_Eternity__TextCreator__

#include "cocos2d.h"

USING_NS_CC;

enum CharacterScale {
    ALL  = 100,
    HARF = 75,
};

class TextCreator
{
    
public:
    TextCreator();
    virtual ~TextCreator();
    
    static Label* create(const std::string text, Point point);
    static Label* create(const std::string text, Point point, Color3B color);
};

#endif /* defined(__Fragment_of_Eternity__TextCreator__) */
