#include "actor/EnemyBossCharacter.h"
#include "core/Constant.h"

USING_NS_CC;

EnemyBossCharacter::EnemyBossCharacter()
: imageEnemy(Constant::EnemyBoss)
{
}

EnemyBossCharacter* EnemyBossCharacter::create()
{
    EnemyBossCharacter *character = new EnemyBossCharacter();
    if (character)
    {
        character->autorelease();
        character->createWithImage();
        return character;
    }
    CC_SAFE_DELETE(character);
    return NULL;
}
