#ifndef __Fragment_of_Eternity__EnemyCharacter__
#define __Fragment_of_Eternity__EnemyCharacter__

#include "cocos2d.h"

USING_NS_CC;

class EnemyCharacter : public Ref
{
private:
    CC_SYNTHESIZE(int, hp, Hp);
    CC_SYNTHESIZE(int, maxHp, MaxHp);
    CC_SYNTHESIZE(Sprite*, image, Image);
    
public:
    EnemyCharacter();
    ~EnemyCharacter();
    static EnemyCharacter* create();
    float getHpPercentage();
};

#endif /* defined(__Fragment_of_Eternity__EnemyEnemyCharacter__) */
