#include "PlayerBattleInfo.h"
#include "Constant.h"

USING_NS_CC;

PlayerBattleInfo::PlayerBattleInfo()
: bp(0)
, burstCount(0)
{
}

PlayerBattleInfo::~PlayerBattleInfo()
{
}

PlayerBattleInfo* PlayerBattleInfo::create()
{
    PlayerBattleInfo *info = new PlayerBattleInfo();
    info->autorelease();
    
    return info;
}

float PlayerBattleInfo::getBpPercentage()
{
    return bp * 100.f / Constant::MAX_PLAYER_BP;
}

void PlayerBattleInfo::incrementBurstCount()
{
    burstCount++;
}
