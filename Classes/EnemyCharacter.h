#ifndef __10sec_BURST__EnemyCharacter__
#define __10sec_BURST__EnemyCharacter__

#include "cocos2d.h"
#include "Constant.h"

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

#endif /* defined(__10sec_BURST__EnemyEnemyCharacter__) */
