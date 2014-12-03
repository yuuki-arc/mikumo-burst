#ifndef __mikumoburst__EnemyBossCharacter__
#define __mikumoburst__EnemyBossCharacter__

#include "cocos2d.h"
#include "actor/EnemyCharacter.h"

USING_NS_CC;

class EnemyBossCharacter : public EnemyCharacter
{
public:
    CC_SYNTHESIZE_READONLY(Constant::ImageEnemy, imageEnemy, ImageEnemy);
    EnemyBossCharacter();
    static EnemyBossCharacter* create();
};

#endif /* defined(__mikumoburst__EnemyEnemyBossCharacter__) */
