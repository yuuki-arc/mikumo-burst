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

