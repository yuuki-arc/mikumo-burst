#include "TextCreator.h"
#include "Constant.h"
#include "GameManager.h"


USING_NS_CC;

TextCreator::TextCreator()
{
    
}

TextCreator::~TextCreator()
{
    
}

Label* TextCreator::create(const std::string text, Point point)
{
    auto label = TextCreator::create(text, point, Constant::NORMAL_FONT());
    
    return label;
}

Label* TextCreator::create(const std::string text, Point point, const std::string fontName)
{
    auto label = Label::createWithBMFont(fontName, text);
    label->setAnchorPoint(Point(0, 0.5));
    label->setScale(BM_FONT_SIZE64(16));
    label->setPosition(point);
    label->getTexture()->setAliasTexParameters();
    
    return label;
}
