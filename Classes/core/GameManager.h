#ifndef __GAME_MANAGER__
#define __GAME_MANAGER__

#include "cocos2d.h"
#include "core/Constant.h"

enum ScreenMode {
    ScreenModeSd,
    ScreenModeHd,
};

enum BattleMode {
    BattleModeNormal,
    BattleModeBoss,
};

class GameManager
{
private:
    GameManager();
    static GameManager* instance;
    Constant::CharaSelect charaSelect;
    CC_SYNTHESIZE(int, battleRank, BattleRank);
    CC_SYNTHESIZE(BattleMode, battleMode, BattleMode);
    
public:
    static GameManager* getInstance();
    
    void initialize();
    
    ScreenMode screenMode;
    bool isScreenModeSd();
    bool isScreenModeHd();

    void setCharaSelect(Constant::CharaSelect charaSelect);
    Constant::CharaSelect getCharaSelect();
    bool isCharaSelectConoha();
    bool isCharaSelectAnzu();
    
    bool isBattleModeNormal();
    bool isBattleModeBoss();
    
    int battleDamagePoint;
    int burstCount;

};

#endif /* defined(__GAME_MANAGER__) */
