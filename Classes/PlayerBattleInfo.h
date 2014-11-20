#ifndef __10sec_BURST__PlayerBattleInfo__
#define __10sec_BURST__PlayerBattleInfo__

#include "cocos2d.h"

USING_NS_CC;

class PlayerBattleInfo : public Ref
{
private:
    CC_SYNTHESIZE(int, bp, Bp);
    CC_SYNTHESIZE(int, burstCount, BurstCount);
    
public:
    PlayerBattleInfo();
    ~PlayerBattleInfo();
    static PlayerBattleInfo* create();
    float getBpPercentage();
    void incrementBurstCount();
};

#endif /* defined(__10sec_BURST__EnemyPlayerBattleInfo__) */
