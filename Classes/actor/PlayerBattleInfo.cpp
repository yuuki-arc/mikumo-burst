#include "actor/PlayerBattleInfo.h"
#include "core/Constant.h"
#include "factory/CharacterCreator.h"

USING_NS_CC;

PlayerBattleInfo::PlayerBattleInfo()
: rank(0)
, bp(0)
, burstCount(0)
, iconImage(nullptr)
, cutInImage1(nullptr)
, cutInImage2(nullptr)
, cutInImage3(nullptr)
{
}

PlayerBattleInfo::~PlayerBattleInfo()
{
}

PlayerBattleInfo* PlayerBattleInfo::create(Constant::CharaSelect charaSelect)
{
    PlayerBattleInfo *info = new PlayerBattleInfo();
    if (info)
    {
        info->autorelease();

        Size visibleSize = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();

        Constant::StringVector list;
        std::string fileName;
        CharacterCreator* creator = new CharacterCreator();

        // キャラクターアイコン
        list = Constant::PERSONA_IMAGE_LIST(Constant::ImagePersona::PersonaIcon);
        fileName = StringUtils::format("%s.png", list[charaSelect].c_str());
        Point position = Point(origin.x + visibleSize.width * 1.5 / 10,
                               origin.y + visibleSize.height * 1 / 10);
        creator->init(CharacterScale::NORMAL);
        info->setIconImage(creator->create(fileName, position));
        
        // カットインアニメーション１
        list = Constant::PERSONA_IMAGE_LIST(Constant::ImagePersona::PersonaBattle1);
        fileName = StringUtils::format("%s.png", list[charaSelect].c_str());
        creator->init(CharacterScale::NORMAL);
        info->setCutInImage1(creator->create(fileName));
        
        // カットインアニメーション２
        list = Constant::PERSONA_IMAGE_LIST(Constant::ImagePersona::PersonaBattle2);
        fileName = StringUtils::format("%s.png", list[charaSelect].c_str());
        creator->init(CharacterScale::NORMAL);
        info->setCutInImage2(creator->create(fileName));
        
        // カットインアニメーション３
        list = Constant::PERSONA_IMAGE_LIST(Constant::ImagePersona::PersonaBattle3);
        fileName = StringUtils::format("%s.png", list[charaSelect].c_str());
        creator->init(CharacterScale::NORMAL);
        info->setCutInImage3(creator->create(fileName));

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
    bp += Constant::BP_INCREMENT + floor(rank / 20);
}
