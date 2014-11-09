#include "UserDataStore.h"
#include "Constant.h"
#include "picojson.h"

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
    setRank(10);

    StringMapVector list = {};
    StringMap map;
    map.insert(std::make_pair(Constant::UserDefaultKey::SCORE_TABLE_RANK(), std::to_string(20)));
    map.insert(std::make_pair(Constant::UserDefaultKey::SCORE_TABLE_SCORE(), std::to_string(20)));
    map.insert(std::make_pair(Constant::UserDefaultKey::SCORE_TABLE_BREAK(), std::to_string(30)));
    list.push_back(map);
    setScoreTable(list);

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

void UserDataStore::setRank(int rank)
{
    userDefault->setIntegerForKey(Constant::UserDefaultKey::RANK(), rank);
    userDefault->flush();
}

int UserDataStore::getRank(int defaultRank)
{
    return userDefault->getIntegerForKey(Constant::UserDefaultKey::RANK(), defaultRank);
}

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
    const std::string KEY_BREAK = Constant::UserDefaultKey::SCORE_TABLE_BREAK();
    
    for (StringMapVector::iterator it = scoreList.begin(); it != scoreList.end(); it++)
    {
        picojson::object detail;
        StringMap map = (*it);
        detail.insert(std::make_pair(KEY_RANK, picojson::value(map[KEY_RANK])));
        detail.insert(std::make_pair(KEY_SCORE, picojson::value(map[KEY_SCORE])));
        detail.insert(std::make_pair(KEY_BREAK, picojson::value(map[KEY_BREAK])));
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
    const std::string KEY_BREAK = Constant::UserDefaultKey::SCORE_TABLE_BREAK();
    
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
        map[KEY_BREAK] = (std::string)jsonMap[KEY_BREAK].get<std::string>();
        result.push_back(map);
    }
    
    return result;
}
