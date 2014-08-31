#include "GameManager.h"

using namespace cocos2d;

GameManager* GameManager::mGameManager = NULL;

GameManager::GameManager()
{
    
}

GameManager* GameManager::getInstance()
{
    if(mGameManager == NULL)
    {
        mGameManager = new GameManager();
        mGameManager->initialize();
    }
    
    return mGameManager;
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
