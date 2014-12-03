#ifndef __mikumoburst__PlayerBattleInfo__
#define __mikumoburst__PlayerBattleInfo__

#include "cocos2d.h"

USING_NS_CC;

class PlayerBattleInfo : public Ref
{
private:
    CC_SYNTHESIZE(int, rank, Rank);
    CC_SYNTHESIZE(int, bp, Bp);
    CC_SYNTHESIZE(int, burstCount, BurstCount);
    CC_SYNTHESIZE(Sprite*, cutInImage, CutInImage);
    
public:
    PlayerBattleInfo();
    ~PlayerBattleInfo();
    static PlayerBattleInfo* create();
    float getBpPercentage();
    void incrementBurstCount();
    void upBpGauge();
};

#endif /* defined(__mikumoburst__EnemyPlayerBattleInfo__) */
