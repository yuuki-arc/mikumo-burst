#include "factory/TextCreator.h"
#include "core/Constant.h"
#include "core/GameManager.h"
#include "core/LabelAttributedBMFont.h"


USING_NS_CC;

TextCreator::TextCreator()
{
    
}

TextCreator::~TextCreator()
{
    
}

/**
 テキスト生成（ビットマップフォント）
 */
Label* TextCreator::create(const std::string text, Point point)
{
    auto label = TextCreator::create(text, point, Constant::NORMAL_FONT());
    
    return label;
}

/**
 テキスト生成（ビットマップフォント）
 */
Label* TextCreator::create(const std::string text, Point point, const std::string fontName)
{
    auto label = Label::createWithBMFont(fontName, text);
    label->setAnchorPoint(Point(0, 0.5));
    label->setScale(BM_FONT_SIZE64(16));
    label->setPosition(point);
    label->getFontAtlas()->setAliasTexParameters();
    
    return label;
}

/**
 文字送り用テキスト生成（ビットマップフォント）
 */
LabelAttributedBMFont* TextCreator::create(const std::vector<std::string> textList, Point point)
{
    auto label = TextCreator::create(textList, point, Constant::NORMAL_FONT());
    
    return label;
}

/**
 文字送り用テキスト生成（ビットマップフォント）
 */
LabelAttributedBMFont* TextCreator::create( std::vector<std::string> textList, Point point, const std::string fontName)
{
    auto label = LabelAttributedBMFont::createWithBMFont(fontName, textList);
    label->setAnchorPoint(Point(0, 0.5));
    label->setScale(BM_FONT_SIZE64(16));
    label->setPosition(point);
    label->getFontAtlas()->setAliasTexParameters();
    
    return label;
}

/**
 テキスト生成（ラベル）
 */
Label* TextCreator::createLabel(const std::string text, Point point)
{
    auto label = TextCreator::createLabel(text, point, Constant::NORMAL_FONT());
    
    return label;
}

/**
 テキスト生成（ラベル）
 */
Label* TextCreator::createLabel(const std::string text, Point point, const std::string fontName)
{
    TTFConfig ttfConfig(LBL_NM_FONT, 16, GlyphCollection::DYNAMIC);
    Label* label;
    label = Label::createWithTTF(ttfConfig, text);
    label->setPosition(point);
    label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    
    return label;
}

