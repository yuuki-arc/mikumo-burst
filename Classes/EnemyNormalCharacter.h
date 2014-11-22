#ifndef __10sec_BURST__EnemyNormalCharacter__
#define __10sec_BURST__EnemyNormalCharacter__

#include "cocos2d.h"
#include "EnemyCharacter.h"

USING_NS_CC;

class EnemyNormalCharacter : public EnemyCharacter
{
public:
    CC_SYNTHESIZE(Constant::ImageEnemy, imageEnemy, ImageEnemy);
    EnemyNormalCharacter();
    static EnemyNormalCharacter* create();
};

#endif /* defined(__10sec_BURST__EnemyEnemyNormalCharacter__) */
