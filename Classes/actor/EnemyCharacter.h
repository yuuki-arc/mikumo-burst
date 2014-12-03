#ifndef __mikumoburst__EnemyCharacter__
#define __mikumoburst__EnemyCharacter__

#include "cocos2d.h"
#include "core/Constant.h"

USING_NS_CC;

class EnemyCharacter : public Ref
{
protected:
    CC_SYNTHESIZE_READONLY(Constant::ImageEnemy, imageEnemy, ImageEnemy);
    CC_SYNTHESIZE(int, hp, Hp);
    CC_SYNTHESIZE(int, maxHp, MaxHp);
    CC_SYNTHESIZE(Sprite*, image, Image);
    
public:
    EnemyCharacter();
    ~EnemyCharacter();
    void createWithImage();
    float getHpPercentage();
    static int getDamage(int chainCount, EnemyCharacter* attacker, EnemyCharacter* defender);
};

#endif /* defined(__mikumoburst__EnemyEnemyCharacter__) */
