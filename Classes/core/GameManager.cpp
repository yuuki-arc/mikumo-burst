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
    charaSelect = Constant::Conoha;
    battleRank = 2;
    battleDamagePoint = 0;
    tapCount = 0;
    burstCount = 0;
}

bool GameManager::isScreenModeSd()
{
    return getInstance()->screenMode == ScreenModeSd ? true : false;
}

bool GameManager::isScreenModeHd()
{
    return getInstance()->screenMode == ScreenModeHd ? true : false;
}

void GameManager::setCharaSelect(Constant::CharaSelect charaSelect)
{
    getInstance()->charaSelect = charaSelect;
}

Constant::CharaSelect GameManager::getCharaSelect()
{
    Constant::CharaSelect charaSelect;
    switch (getInstance()->battleMode) {
        case BattleModeNormal:
            charaSelect = getInstance()->charaSelect;
            break;
        case BattleModeBoss:
            charaSelect = Constant::CharaSelect::VsBoss;
            break;
        default:
            charaSelect = getInstance()->charaSelect;
            break;
    }
    return charaSelect;
}

bool GameManager::isCharaSelectConoha()
{
    return getInstance()->charaSelect == Constant::Conoha ? true : false;
}

bool GameManager::isCharaSelectAnzu()
{
    return getInstance()->charaSelect == Constant::Anzu ? true : false;
}

bool GameManager::isBattleModeNormal()
{
    return getInstance()->battleMode == BattleModeNormal ? true : false;
}

bool GameManager::isBattleModeBoss()
{
    return getInstance()->battleMode == BattleModeBoss ? true : false;
}
