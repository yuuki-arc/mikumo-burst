#include "actor/EnemyNormalCharacter.h"
#include "core/Constant.h"

USING_NS_CC;

EnemyNormalCharacter::EnemyNormalCharacter()
: imageEnemy(Constant::EnemyNormal)
{
}

EnemyNormalCharacter* EnemyNormalCharacter::create()
{
    EnemyNormalCharacter *character = new EnemyNormalCharacter();
    if (character)
    {
        character->autorelease();
        character->createWithImage();
        return character;
    }
    CC_SAFE_DELETE(character);
    return NULL;
}
