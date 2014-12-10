#include "actor/EnemyCharacter.h"
#include "core/Constant.h"
#include "core/GameManager.h"
#include "factory/CharacterCreator.h"

USING_NS_CC;

EnemyCharacter::EnemyCharacter()
: imageEnemy()
, hp(0)
, maxHp(0)
, image(nullptr)
{
}

EnemyCharacter::~EnemyCharacter()
{
}

void EnemyCharacter::createWithImage()
{
    int hp;
    int rank10UpBase = floor(GameManager::getInstance()->getBattleRank() / 10);
    
    if (GameManager::getInstance()->isBattleModeNormal())
    {
        hp = Constant::DEFAULT_ENEMY_HP +
             rank10UpBase * Constant::HP_RANK_10_UP_INCREMENT;
    }
    else
    {
        hp = Constant::DEFAULT_ENEMY_BOSS_HP +
             rank10UpBase * Constant::HP_RANK_10_UP_BOSS_INCREMENT;
    }
    this->setMaxHp(hp);
    this->setHp(hp);
    
    Constant::StringVector enemyImageList = Constant::ENEMY_IMAGE_LIST(getImageEnemy());
    int num = arc4random() % enemyImageList.size();
    std::string enemyFileName = StringUtils::format("%s.png", enemyImageList.at(num).c_str());
    
    CharacterCreator* creator = new CharacterCreator();
    creator->init(CharacterScale::DOUBLE);
    this->setImage(creator->create(enemyFileName));
}

float EnemyCharacter::getHpPercentage()
{
    return hp * 100.f / maxHp;
}
