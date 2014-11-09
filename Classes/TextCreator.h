#ifndef __Fragment_of_Eternity__TextCreator__
#define __Fragment_of_Eternity__TextCreator__

#include "cocos2d.h"

USING_NS_CC;

class TextCreator
{
    
public:
    TextCreator();
    virtual ~TextCreator();
    
    static Label* create(const std::string text, Point point);
    static Label* create(const std::string text, Point point, const std::string fontName);
};

#endif /* defined(__Fragment_of_Eternity__TextCreator__) */
