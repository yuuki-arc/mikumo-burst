#include "actor/PlayerBattleInfo.h"
#include "core/Constant.h"
#include "factory/CharacterCreator.h"

USING_NS_CC;

PlayerBattleInfo::PlayerBattleInfo()
: rank(0)
, bp(0)
, burstCount(0)
, cutInImage(nullptr)
{
}

PlayerBattleInfo::~PlayerBattleInfo()
{
}

PlayerBattleInfo* PlayerBattleInfo::create()
{
    PlayerBattleInfo *info = new PlayerBattleInfo();
    if (info)
    {
        info->autorelease();

        Constant::StringVector imageList = Constant::Constant::PERSONA_IMAGE_LIST();
        std::string fileName = StringUtils::format("%s.png", Constant::PERSONA_IMAGE_LIST().at(1).c_str());
        CCLOG("PlayerBattleInfo: %s", fileName.c_str());
        CharacterCreator* creator = new CharacterCreator();
        creator->init(CharacterScale::ALL);
        info->setCutInImage(creator->create(fileName));

        return info;
    }
    CC_SAFE_DELETE(info);
    return NULL;
}

float PlayerBattleInfo::getBpPercentage()
{
    return bp * 100.f / Constant::MAX_PLAYER_BP;
}

void PlayerBattleInfo::incrementBurstCount()
{
    burstCount++;
}

void PlayerBattleInfo::upBpGauge()
{
    bp += Constant::BP_INCREMENT + floor(rank / 10);
}
