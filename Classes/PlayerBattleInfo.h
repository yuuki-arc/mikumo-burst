#ifndef __Fragment_of_Eternity__PlayerBattleInfo__
#define __Fragment_of_Eternity__PlayerBattleInfo__

#include "cocos2d.h"

USING_NS_CC;

class PlayerBattleInfo : public Ref
{
private:
    CC_SYNTHESIZE(int, ep, Ep);
    CC_SYNTHESIZE(int, battleEpCount, battleEpCount);
    
public:
    PlayerBattleInfo();
    ~PlayerBattleInfo();
    static PlayerBattleInfo* create();
    float getEpPercentage();
    void incrementBattleEpCount();
};

#endif /* defined(__Fragment_of_Eternity__EnemyPlayerBattleInfo__) */
