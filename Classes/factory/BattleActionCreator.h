#ifndef __10sec_BURST__BattleActionCreator__
#define __10sec_BURST__BattleActionCreator__

#include "cocos2d.h"

USING_NS_CC;

class BattleActionCreator
{
    
public:
    BattleActionCreator();
    virtual ~BattleActionCreator();

    static ActionInterval* appearEnemy();
    static ActionInterval* attackToEnemy();
    static ActionInterval* damageToEnemy();
    static ActionInterval* damageToEnemy2();
    static ActionInterval* damageToEnemy3();
    static ActionInterval* defeatEnemy();
    
};

#endif /* defined(__10sec_BURST__BattleActionCreator__) */
