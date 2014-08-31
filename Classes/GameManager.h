#ifndef __GAME_MANAGER__
#define __GAME_MANAGER__

#include "cocos2d.h"

typedef enum{
    ScreenModeSd ,
    ScreenModeHd ,
}ScreenMode;

class GameManager
{
private:
    GameManager();
    static GameManager* m_mySingleton;
    
public:
    static GameManager* sharedGameManager();
    
    ScreenMode screenMode;
    bool isScreenModeSd();
    bool isScreenModeHd();

};

#endif /* defined(__GAME_MANAGER__) */
