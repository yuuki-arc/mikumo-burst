#include "GameManager.h"

using namespace cocos2d;

//All static variables need to be defined in the .cpp file
//I've added this following line to fix the problem
GameManager* GameManager::m_mySingleton = NULL;

GameManager::GameManager()
{
    
}

GameManager* GameManager::sharedGameManager()
{
    //If the singleton has no instance yet, create one
    if(NULL == m_mySingleton)
    {
        //Create an instance to the singleton
        m_mySingleton = new GameManager();
    }
    
    //Return the singleton object
    return m_mySingleton;
}

bool GameManager::isScreenModeSd()
{
    return GameManager::sharedGameManager()->screenMode == ScreenModeSd ? true : false;
}

bool GameManager::isScreenModeHd()
{
    return GameManager::sharedGameManager()->screenMode == ScreenModeHd ? true : false;
}
