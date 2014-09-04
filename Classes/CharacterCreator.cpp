#include "CharacterCreator.h"
#include "GameManager.h"

USING_NS_CC;

CharacterCreator::CharacterCreator()
{
    
}

CharacterCreator::~CharacterCreator()
{
    
}

Sprite* CharacterCreator::create(const std::string &filename, CharacterScale characterScale)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    Sprite* character = Sprite::createWithSpriteFrameName(filename);
    character->setPosition(Point(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height * 6 / 10));
    
    float scale = character->getScale() * characterScale / 100;
    if (GameManager::getInstance()->isScreenModeSd())
    {
        scale /= 2;
    }
    character->setScale(scale, scale);
    
    return character;
}
