#ifndef __mikumoburst__BattleActionCreator__
#define __mikumoburst__BattleActionCreator__

#include "cocos2d.h"

USING_NS_CC;

class BattleActionCreator
{
    
public:
    BattleActionCreator();
    virtual ~BattleActionCreator();

    static ActionInterval* appearEnemy();
    static ActionInterval* attackToEnemy();
    static ActionInterval* burstCutIn(Sprite *sprite, CallFunc *callback);
    static ActionInterval* damageToEnemy();
    static ActionInterval* damageToEnemy2();
    static ActionInterval* damageToEnemy3();
    static ActionInterval* defeatEnemy();
    
};

#endif /* defined(__mikumoburst__BattleActionCreator__) */
