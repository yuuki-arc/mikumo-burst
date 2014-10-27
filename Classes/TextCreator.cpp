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
    auto label = Label::createWithBMFont("Arial_Black.fnt", text);
    label->setAnchorPoint(Point(0, 0.5));
    label->setScale(BM_FONT_SIZE64(16));
    label->setPosition(point);
    label->getTexture()->setAliasTexParameters();
    
    return label;
}

Label* TextCreator::create(const std::string text, Point point, Color3B color)
{
    auto label = TextCreator::create(text, point);
    label->setColor(color);
    
    return label;
}
