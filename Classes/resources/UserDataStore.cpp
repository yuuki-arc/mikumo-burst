#include "UserDataStore.h"
#include "core/Constant.h"
#include "core/picojson.h"

USING_NS_CC;

UserDataStore* UserDataStore::instance = NULL;

UserDataStore::UserDataStore()
{
    
}

UserDataStore* UserDataStore::getInstance()
{
    if(instance == NULL)
    {
        instance = new UserDataStore();
        instance->initialize();
    }
    
    return instance;
}

void UserDataStore::initialize()
{
    userDefault = UserDefault::getInstance();
}


void UserDataStore::setupData()
{
    setDataStoredOn();
    setTotalRank(1 + 1);
    setRankList(getDefaultRankList());
    
//    StringMapVector list = {};
//    StringMap map;
//    map.insert(std::make_pair(Constant::UserDefaultKey::SCORE_TABLE_RANK(), std::to_string(20)));
//    map.insert(std::make_pair(Constant::UserDefaultKey::SCORE_TABLE_SCORE(), std::to_string(20)));
//    map.insert(std::make_pair(Constant::UserDefaultKey::SCORE_TABLE_BURST(), std::to_string(30)));
//    list.push_back(map);
//    setScoreTable(list);
}

StringMapVector UserDataStore::getDefaultRankList()
{
    StringMapVector list = {};
    StringMap map;
    map[Constant::charaKey(Constant::Conoha)] = "1";
    map[Constant::charaKey(Constant::Anzu)] = "1";
    list.push_back(map);
    return list;
}

void UserDataStore::setDataStoredOn()
{
    userDefault->setBoolForKey(Constant::UserDefaultKey::DATA_STORED(), true);
    userDefault->flush();
}

bool UserDataStore::isDataStored()
{
    return userDefault->getBoolForKey(Constant::UserDefaultKey::DATA_STORED(), false);
}

void UserDataStore::setBattleCount(int value)
{
    userDefault->setIntegerForKey(Constant::UserDefaultKey::BATTLE_COUNT(), value);
    userDefault->flush();
}

int UserDataStore::getBattleCount()
{
    return userDefault->getIntegerForKey(Constant::UserDefaultKey::BATTLE_COUNT());
}

void UserDataStore::setTotalRank(int value)
{
    userDefault->setIntegerForKey(Constant::UserDefaultKey::TOTAL_RANK(), value);
    userDefault->flush();
}

int UserDataStore::getTotalRank()
{
    return userDefault->getIntegerForKey(Constant::UserDefaultKey::TOTAL_RANK());
}

void UserDataStore::setRankList(StringMapVector rankList)
{
    picojson::value value;
    picojson::array detail_list;
    
    for (StringMapVector::iterator it = rankList.begin(); it != rankList.end(); it++)
    {
        picojson::object detail;
        StringMap map = (*it);
        detail.insert({"conoha", picojson::value(map["conoha"])});
        detail.insert({"anzu", picojson::value(map["anzu"])});
        detail_list.push_back(picojson::value(detail));
    }
    value = picojson::value(detail_list);
    userDefault->setStringForKey(Constant::UserDefaultKey::RANK_LIST(), value.serialize());
    userDefault->flush();
}

StringMapVector UserDataStore::getRankList()
{
    StringMapVector result = {};
    
    std::string list = "";
    list = userDefault->getStringForKey(Constant::UserDefaultKey::RANK_LIST(), "");
    if (list.empty())
    {
        setRankList(getDefaultRankList());
        list = userDefault->getStringForKey(Constant::UserDefaultKey::RANK_LIST(), "");
    }
    
    picojson::value v;
    std::string err;
    picojson::parse(v, list.begin(), list.end(), &err);
    picojson::array& array = v.get<picojson::array>();
    for (picojson::array::iterator it = array.begin(); it != array.end(); it++)
    {
        StringMap map;
        picojson::object& jsonMap = it->get<picojson::object>();
        map["conoha"] = (std::string)jsonMap["conoha"].get<std::string>();
        map["anzu"] = (std::string)jsonMap["anzu"].get<std::string>();
        result.push_back(map);
    }
    
    return result;
}

void UserDataStore::setTotalScore(int value)
{
    userDefault->setIntegerForKey(Constant::UserDefaultKey::TOTAL_SCORE(), value);
    userDefault->flush();
}

int UserDataStore::getTotalScore()
{
    return userDefault->getIntegerForKey(Constant::UserDefaultKey::TOTAL_SCORE());
}

void UserDataStore::setTotalHit(int value)
{
    userDefault->setIntegerForKey(Constant::UserDefaultKey::TOTAL_HIT(), value);
    userDefault->flush();
}

int UserDataStore::getTotalHit()
{
    return userDefault->getIntegerForKey(Constant::UserDefaultKey::TOTAL_HIT());
}

void UserDataStore::setTotalBurst(int value)
{
    userDefault->setIntegerForKey(Constant::UserDefaultKey::TOTAL_BURST(), value);
    userDefault->flush();
}

int UserDataStore::getTotalBurst()
{
    return userDefault->getIntegerForKey(Constant::UserDefaultKey::TOTAL_BURST());
}

/*
void UserDataStore::setScoreTable(StringMapVector scoreList)
{
    // {
    //   1: {"chain":200, "score":12300},
    //   2: {"chain":200, "score":12300},
    //   3: {"chain":200, "score":12300},
    //   4: {"chain":200, "score":12300},
    //   5: {"chain":200, "score":12300},
    // }
    //
    //    picojson::object detail;
    //    detail.insert(std::make_pair("chain", picojson::value(std::string("200"))));
    //    detail.insert(std::make_pair("score", picojson::value(std::string("12300"))));
    //    detail_list.push_back(picojson::value(detail));
    //    
    //    picojson::object detail2;
    //    detail2.insert(std::make_pair("chain", picojson::value(std::string("400"))));
    //    detail2.insert(std::make_pair("score", picojson::value(std::string("25000"))));
    //    detail_list.push_back(picojson::value(detail2));
    //    value = picojson::value(detail_list);
    //    CCLOG("%s", value.serialize().c_str());
    //    userDefault->setStringForKey("ranking", value.serialize());

    picojson::value value;
    picojson::array detail_list;
    
    const std::string KEY_RANK = Constant::UserDefaultKey::SCORE_TABLE_RANK();
    const std::string KEY_SCORE = Constant::UserDefaultKey::SCORE_TABLE_SCORE();
    const std::string KEY_BURST = Constant::UserDefaultKey::SCORE_TABLE_BURST();
    
    for (StringMapVector::iterator it = scoreList.begin(); it != scoreList.end(); it++)
    {
        picojson::object detail;
        StringMap map = (*it);
        detail.insert(std::make_pair(KEY_RANK, picojson::value(map[KEY_RANK])));
        detail.insert(std::make_pair(KEY_SCORE, picojson::value(map[KEY_SCORE])));
        detail.insert(std::make_pair(KEY_BURST, picojson::value(map[KEY_BURST])));
        detail_list.push_back(picojson::value(detail));
    }
    value = picojson::value(detail_list);
    userDefault->setStringForKey(Constant::UserDefaultKey::SCORE_TABLE(), value.serialize());
    
//    picojson::array& array = value["1"].get<picojson::array>();
//    for (picojson::array::iterator it = array.begin(); it != array.end(); it++)
//    {
//        picojson::object& tmpObject = it->get<picojson::object>();
//        int chain = (int)tmpObject["chain"].get<double>();
//        int score = (int)tmpObject["score"].get<double>();
//        CCLOG("chain:%d, score:%d", chain, score);
//    }
//
//    list.data();
//    picojson::value v;
//    picojson::parse(v, list);
//    picojson::parse(list.)
//    picojson::object& all = v.get<picojson::object>();
//    picojson::array& array = all["hoge"].get<picojson::array>();
//    for (picojson::array::iterator it = array.begin(); it != array.end(); it++)
//    {
//        picojson::object& tmpObject = it->get<picojson::object>();
//        int x = (int)tmpObject["x"].get<double>();
//        int y = (int)tmpObject["y"].get<double>();
//        int z = (int)tmpObject["z"].get<double>();
//        CCLOG("x:%d, y:%d, z:%d", x, y, z);
//    }
    userDefault->flush();
}

StringMapVector UserDataStore::getScoreTable()
{
    StringMapVector result = {};
    
    std::string list = "";
    list = userDefault->getStringForKey(Constant::UserDefaultKey::SCORE_TABLE(), "");
    
    const std::string KEY_RANK = Constant::UserDefaultKey::SCORE_TABLE_RANK();
    const std::string KEY_SCORE = Constant::UserDefaultKey::SCORE_TABLE_SCORE();
    const std::string KEY_BURST = Constant::UserDefaultKey::SCORE_TABLE_BURST();
    
    picojson::value v;
    std::string err;
    picojson::parse(v, list.begin(), list.end(), &err);
    picojson::array& array = v.get<picojson::array>();
    for (picojson::array::iterator it = array.begin(); it != array.end(); it++)
    {
        StringMap map;
        picojson::object& jsonMap = it->get<picojson::object>();
        map[KEY_RANK] = (std::string)jsonMap[KEY_RANK].get<std::string>();
        map[KEY_SCORE] = (std::string)jsonMap[KEY_SCORE].get<std::string>();
        map[KEY_BURST] = (std::string)jsonMap[KEY_BURST].get<std::string>();
        result.push_back(map);
    }
    
    return result;
}
*/
