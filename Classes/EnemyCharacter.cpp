#include "EnemyCharacter.h"

USING_NS_CC;

EnemyCharacter::EnemyCharacter()
: hp(0)
, maxHp(0)
, image(nullptr)
{
}

EnemyCharacter::~EnemyCharacter()
{
}

EnemyCharacter* EnemyCharacter::create()
{
    EnemyCharacter *character = new EnemyCharacter();
    character->autorelease();
    
    return character;
}

float EnemyCharacter::getHpPercentage()
{
    return hp * 100.f / maxHp;
}

int EnemyCharacter::getDamage(int chainCount, EnemyCharacter* attacker, EnemyCharacter* defender)
{
    // 消したボールの個数によるダメージ
    float baseDamage = 0;
    
    // 連鎖ボーナス
    float chainBonus = powf(1.1, chainCount - 1);
    
    // ダメージにボーナスを乗算したものを返す
    return baseDamage * chainBonus;
}
