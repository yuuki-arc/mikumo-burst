#ifndef __Fragment_of_Eternity__PlayerBattleInfo__
#define __Fragment_of_Eternity__PlayerBattleInfo__

#include "cocos2d.h"

USING_NS_CC;

class PlayerBattleInfo : public Ref
{
private:
    CC_SYNTHESIZE(int, ep, Ep);
    
public:
    PlayerBattleInfo();
    ~PlayerBattleInfo();
    static PlayerBattleInfo* create();
    float getEpPercentage();
};

#endif /* defined(__Fragment_of_Eternity__EnemyPlayerBattleInfo__) */
