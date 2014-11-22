#include "EnemyBossCharacter.h"
#include "Constant.h"

USING_NS_CC;

EnemyBossCharacter::EnemyBossCharacter()
: imageEnemy(Constant::EnemyBoss)
{
}

EnemyBossCharacter* EnemyBossCharacter::create()
{
    EnemyBossCharacter *character = new EnemyBossCharacter();
    character->autorelease();
    character->createWithImage();
    
    return character;
}
