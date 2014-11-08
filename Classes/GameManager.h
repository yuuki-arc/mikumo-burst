#ifndef __GAME_MANAGER__
#define __GAME_MANAGER__

#include "cocos2d.h"

enum ScreenMode {
    ScreenModeSd ,
    ScreenModeHd ,
};

class GameManager
{
private:
    GameManager();
    static GameManager* instance;
    
public:
    static GameManager* getInstance();
    
    void initialize();
    
    ScreenMode screenMode;
    bool isScreenModeSd();
    bool isScreenModeHd();
    
    int currentRank;
    int battleDamagePoint;
    int battleEternityPoint;

};

#endif /* defined(__GAME_MANAGER__) */
