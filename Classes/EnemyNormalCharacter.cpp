#include "EnemyNormalCharacter.h"
#include "Constant.h"

USING_NS_CC;

EnemyNormalCharacter::EnemyNormalCharacter()
: imageEnemy(Constant::EnemyNormal)
{
}

EnemyNormalCharacter* EnemyNormalCharacter::create()
{
    EnemyNormalCharacter *character = new EnemyNormalCharacter();
    character->autorelease();
    character->createWithImage();
    
    return character;
}
