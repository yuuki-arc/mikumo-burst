#include "EnemyBossCharacter.h"
#include "Constant.h"
#include "GameManager.h"
#include "CharacterCreator.h"

USING_NS_CC;

EnemyBossCharacter* EnemyBossCharacter::create()
{
    EnemyBossCharacter *character = new EnemyBossCharacter();
    character->autorelease();
    int hp = Constant::DEFAULT_ENEMY_BOSS_HP +
             GameManager::getInstance()->getRank() * Constant::HP_RANK_UP_INCREMENT;
    character->setMaxHp(hp);
    character->setHp(hp);
    
    Constant::StringVector enemyImageList = Constant::ENEMY_IMAGE_LIST(Constant::EnemyBoss);
    int num = CCRANDOM_0_1() * enemyImageList.size();
    std::string enemyFileName = StringUtils::format("%s.png", enemyImageList.at(num).c_str());

    CharacterCreator* creator = new CharacterCreator();
    creator->init(CharacterScale::ALL);
    character->setImage(creator->create(enemyFileName));
    
    return character;
}
