#include "BattleAnimationCreator.h"
#include "GameManager.h"

USING_NS_CC;

BattleAnimationCreator::BattleAnimationCreator()
{
    
}

BattleAnimationCreator::~BattleAnimationCreator()
{
    
}

ActionInterval* attackEnemy()
{
    return Sequence::create(Spawn::create(MoveBy::create(1.5f, Vec2(0,50)),
                                          FadeOut::create(1.5f), NULL),
                                          CallFuncN::create([&](Node *node){
                                              node->removeFromParent();
                                          }),
                            NULL);
}
