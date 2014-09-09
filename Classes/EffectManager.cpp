#include "EffectManager.h"
#include "GameManager.h"
#include "cocos2d.h"

USING_NS_CC;

bool EffectManager::init()
{
    SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();
    spriteFrameCache->addSpriteFramesWithFile("effect/battleEffect0.plist");
    if (GameManager::getInstance()->isScreenModeHd())
    {
        spriteFrameCache->addSpriteFramesWithFile("effect/battleEffect1.plist");
    }
    
    return true;
}

Sprite* EffectManager::effectPurified(std::string effectName, int count, Point location)
{
    SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();
    auto frames = new Vector<SpriteFrame *>();
    for (int i = 0; i < count; i++)
    {
        std::string imageFileName = StringUtils::format("%s-%d.png", effectName.c_str() , i);
        frames->pushBack(spriteFrameCache->getSpriteFrameByName(imageFileName));
    }
    Animation *animation = Animation::createWithSpriteFrames(*frames, 0.1f);
    animation->setRestoreOriginalFrame(false);
    animation->setLoops(1);
    Animate *animateAction = Animate::create(animation);
    delete frames;

    auto sprite2 = Sprite::create();
    sprite2->setAnchorPoint(Vec2(0.5,0.5));
    sprite2->runAction(
        Sequence::create(animateAction,
            CallFunc::create([sprite2]()
            {
                sprite2->removeFromParentAndCleanup(true);
            }),
        NULL));
    sprite2->setPosition(location);
    
    return sprite2;
}
