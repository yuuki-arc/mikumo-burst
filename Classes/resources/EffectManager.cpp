#include "resources/EffectManager.h"
#include "core/GameManager.h"
#include "cocos2d.h"

USING_NS_CC;

Sprite* EffectManager::effectPurified(std::string effectName, Point location, float scale, float delay)
{
    Animate* animateAction = createFrameAnimation(effectName, location, scale, delay);
    
    auto sprite2 = Sprite::create();
    sprite2->setAnchorPoint(Vec2(0.5,0.5));
    sprite2->setScale(scale);
    sprite2->runAction(
        Sequence::create(
            animateAction,
            CallFunc::create([sprite2]()
            {
                sprite2->removeFromParentAndCleanup(true);
            }),
        nullptr));
    sprite2->setPosition(location);
    
    return sprite2;
}

Sprite* EffectManager::effectPurifiedTwice(std::string effectName, Point location, float scale, float delay)
{
    Animate* animateAction1 = createFrameAnimation(effectName, location, scale, delay);
    Animate* animateAction2 = animateAction1->clone();
    
    ActionInterval* moveAction1 = MoveBy::create(delay, Vec2(50, 50));
    ActionInterval* moveAction2 = MoveBy::create(delay, Vec2(50, 50));
    Spawn* spawn1 = Spawn::create(animateAction1, moveAction1, NULL);
    Spawn* spawn2 = Spawn::create(animateAction2, moveAction2, NULL);

    auto sprite2 = Sprite::create();
    sprite2->setAnchorPoint(Vec2(0.5,0.5));
    sprite2->runAction(
        Sequence::create(
            CCEaseIn::create(spawn1, 2),
            CCEaseIn::create(spawn2, 2),
            CallFunc::create([sprite2]()
            {
                sprite2->removeFromParentAndCleanup(true);
            }),
         nullptr));
    sprite2->setPosition(location);
    
    return sprite2;
}

Animate* EffectManager::createFrameAnimation(std::string effectName, Point location, float scale, float delay)
{
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    auto frames = new Vector<SpriteFrame *>();
    //    for (int i = 0; i < count; i++)
    int i = 0;
    while (true)
    {
        std::string imageFileName = StringUtils::format("%s-%d.png", effectName.c_str() , i);
        auto frame = spriteFrameCache->getSpriteFrameByName(imageFileName);
        if (!frame) break;
        frames->pushBack(frame);
        i++;
    }
    Animation *animation = Animation::createWithSpriteFrames(*frames, delay);
    animation->setRestoreOriginalFrame(false);
    animation->setLoops(1);
    Animate *animateAction = Animate::create(animation);
    delete frames;
    
    return animateAction;
}
