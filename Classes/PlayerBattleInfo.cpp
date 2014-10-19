#include "PlayerBattleInfo.h"
#include "Constant.h"

USING_NS_CC;

PlayerBattleInfo::PlayerBattleInfo()
: ep(0)
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

float PlayerBattleInfo::getEpPercentage()
{
    return ep * 100.f / Constant::MAX_PLAYER_EP;
}

void PlayerBattleInfo::incrementBattleEpCount()
{
    battleEpCount++;
}
