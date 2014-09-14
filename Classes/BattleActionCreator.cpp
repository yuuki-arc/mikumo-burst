#include "BattleActionCreator.h"
#include "GameManager.h"

USING_NS_CC;

BattleActionCreator::BattleActionCreator()
{
    
}

BattleActionCreator::~BattleActionCreator()
{
    
}

ActionInterval* BattleActionCreator::appearEnemy()
{
    ActionInterval* action1 = Lens3D::create(10, Size(32,24), Vec2(100,180), 150);
    ActionInterval* action2 = Waves3D::create(10, Size(15,10), 18, 15);
    ActionInterval* action =
        Sequence::create(action1,
                         action2,
                         action2->reverse(),
                         action1->reverse(),
                         StopGrid::create(),
                         NULL);
    return action;
}

ActionInterval* BattleActionCreator::attackToEnemy()
{
    ActionInterval* action =
        Sequence::create(Spawn::create(MoveBy::create(1.5f, Vec2(0,50)),
                                       FadeOut::create(1.5f), NULL),
                                       CallFuncN::create([&](Node *node){
                                           node->removeFromParent();
                                       }),
                         NULL);
    return action;
}

ActionInterval* BattleActionCreator::damageToEnemy()
{
    ActionInterval* actionShaky = Shaky3D::create(0.1f, Size(100,100), 5, true);
    ActionInterval* action =
        Sequence::create(DelayTime::create(0.2f),
                         actionShaky,
                         actionShaky->reverse(),
                         StopGrid::create(),
                         NULL);
    return action;
}

ActionInterval* BattleActionCreator::damageToEnemy2()
{
    ActionInterval* actionShaky = ShakyTiles3D::create(0.1f, Size(100,100), 10, true);
    ActionInterval* action =
    Sequence::create(DelayTime::create(0.2f),
                     actionShaky,
                     actionShaky->reverse(),
                     StopGrid::create(),
                     NULL);
    return action;
}

ActionInterval* BattleActionCreator::damageToEnemy3()
{
    PointArray* points = PointArray::create(3);
    points->addControlPoint(Size(0,0));
    points->addControlPoint(Size(0,10));
    points->addControlPoint(Size(0,0));
    ActionInterval* actionOne = CardinalSplineBy::create(0.2f, points, 5.0f);
    ActionInterval* action =
        Sequence::create(actionOne,
                         actionOne->reverse(),
                         NULL);
    return action;
}

ActionInterval* BattleActionCreator::defeatEnemy()
{
    PointArray* points = PointArray::create(3);
    points->addControlPoint(Size(0,0));
    points->addControlPoint(Size(0,10));
    points->addControlPoint(Size(0,0));
    ActionInterval* action =
    Sequence::create(CardinalSplineBy::create(0.2f, points, 5.0f),
                     NULL);
    return action;
}
