#ifndef __mikumoburst__TextCreator__
#define __mikumoburst__TextCreator__

#include "cocos2d.h"
#include "core/LabelAttributedBMFont.h"

USING_NS_CC;

class TextCreator
{
    
public:
    TextCreator();
    virtual ~TextCreator();
    
    static Label* create(const std::string text, Point point);
    static Label* create(const std::string text, Point point, const std::string fontName);
    static LabelAttributedBMFont* create(const std::vector<std::string> textList, Point point);
    static LabelAttributedBMFont* create(const std::vector<std::string> textList, Point point, const std::string fontName);
};

#endif /* defined(__mikumoburst__TextCreator__) */
