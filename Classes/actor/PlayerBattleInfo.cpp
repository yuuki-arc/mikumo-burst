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

        Constant::StringVector list = Constant::PERSONA_IMAGE_LIST(Constant::ImagePersona::PersonaBattle1);
        std::string fileName = StringUtils::format("%s.png", list[0].c_str());
        CCLOG("PlayerBattleInfo: %s", fileName.c_str());
        CharacterCreator* creator = new CharacterCreator();
        creator->init(CharacterScale::NORMAL);
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
