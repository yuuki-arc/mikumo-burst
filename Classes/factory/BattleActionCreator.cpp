#include "factory/BattleActionCreator.h"
#include "core/GameManager.h"

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

ActionInterval* BattleActionCreator::burstCutIn(Sprite *sprite, CallFunc *callback)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    // アニメーション前設定
    sprite->setVisible(false);
    sprite->setOpacity(255);
    sprite->setScale(0.2f, 0.2f);
    sprite->setPosition(Point(0, 0));
    sprite->setVisible(true);

    // アニメーション処理
    auto scaleAction = ScaleTo::create(0.5f, 1);
    ccBezierConfig bezier;
    int pattern = arc4random() % 2;
       if (pattern == 0)
    {
        bezier.controlPoint_1 = Point(origin.x + visibleSize.width, 0);
        bezier.controlPoint_2 = Point(origin.x + visibleSize.width * 2, origin.y + visibleSize.height * 1.8f);
    }
    else
    {
        bezier.controlPoint_1 = Point(0, origin.y + visibleSize.height);
        bezier.controlPoint_2 = Point(origin.x + visibleSize.width * 1.5f, origin.y + visibleSize.height * 2);
    }
    bezier.endPosition = Point(origin.x + visibleSize.width / 2,
                               origin.y + visibleSize.height / 2);
    auto moveAction = BezierBy::create(0.5f, bezier);
    auto easeAction = EaseInOut::create(moveAction, 3);
    auto spawn1 = Spawn::create(scaleAction, easeAction, NULL);
    
    auto scaleAction2 = ScaleTo::create(0.3f, 4);
    auto fadeOutAction = FadeOut::create(0.3f);
    auto spawn2 = Spawn::create(scaleAction2, fadeOutAction, NULL);
    
    ActionInterval* action =
        Sequence::create(spawn1,
                         DelayTime::create(0.5f),
                         spawn2,
                         callback,
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
    points->addControlPoint(Size(0, 0));
    points->addControlPoint(Size(arc4random()%20 - 10.0f, arc4random()%20 - 10.0f));
    points->addControlPoint(Size(0, 0));
    ActionInterval* actionOne = CardinalSplineBy::create(0.2f, points, 5.0f);
    ActionInterval* action =
        Sequence::create(actionOne,
                         actionOne->reverse(),
                         NULL);
    return action;
}

ActionInterval* BattleActionCreator::defeatEnemy()
{
    ActionInterval* actionTintTo = TintTo::create(0.2f, 255, 255, 255);
    ActionInterval* actionFadeOut = FadeOutUpTiles::create(4.0f, Size(100,200));
    ActionInterval* action =
        Sequence::create(actionTintTo,
                         actionFadeOut,
                             NULL);
    return action;
}
