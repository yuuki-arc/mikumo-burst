#include "core/GameManager.h"
#include "core/Constant.h"
#include "resources/UserDataStore.h"

USING_NS_CC;

GameManager* GameManager::instance = NULL;

GameManager::GameManager()
{
    
}

GameManager* GameManager::getInstance()
{
    if(instance == NULL)
    {
        instance = new GameManager();
        instance->initialize();
    }
    
    return instance;
}

void GameManager::initialize()
{
    
}

bool GameManager::isScreenModeSd()
{
    return GameManager::getInstance()->screenMode == ScreenModeSd ? true : false;
}

bool GameManager::isScreenModeHd()
{
    return GameManager::getInstance()->screenMode == ScreenModeHd ? true : false;
}

bool GameManager::isBattleModeNormal()
{
    return GameManager::getInstance()->battleMode == BattleModeNormal ? true : false;
}

bool GameManager::isBattleModeBoss()
{
    return GameManager::getInstance()->battleMode == BattleModeBoss ? true : false;
}

int GameManager::getRank()
{
    int battleRank = UserDataStore::getInstance()->getRank() + 1;
    if (battleRank > Constant::LIMIT_RANK)
    {
        battleRank = Constant::LIMIT_RANK;
    }
    return battleRank;
}
