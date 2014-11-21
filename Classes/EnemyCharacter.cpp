#include "EnemyCharacter.h"
#include "Constant.h"
#include "CharacterCreator.h"

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

EnemyCharacter* EnemyCharacter::create(EnemyCharacter* character, int hp, Constant::ImageEnemy imageEnemy)
{
    character->setMaxHp(hp);
    character->setHp(hp);
    
    Constant::StringVector enemyImageList = Constant::ENEMY_IMAGE_LIST(imageEnemy);
    int num = CCRANDOM_0_1() * enemyImageList.size();
    std::string enemyFileName = StringUtils::format("%s.png", enemyImageList.at(num).c_str());
    
    CharacterCreator* creator = new CharacterCreator();
    creator->init(CharacterScale::ALL);
    character->setImage(creator->create(enemyFileName));
    
    return character;
}

float EnemyCharacter::getHpPercentage()
{
    return hp * 100.f / maxHp;
}
