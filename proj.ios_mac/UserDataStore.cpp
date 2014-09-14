#include "UserDataStore.h"
#include "Constant.h"
#include "picojson.h"

USING_NS_CC;

UserDataStore::UserDataStore()
{
    
}

int UserDataStore::getRank(int defaultRank)
{
    UserDefault* userDefault = UserDefault::getInstance();
    return userDefault->getIntegerForKey(Constant::UserDefaultKey::RANK(), defaultRank);
}

void UserDataStore::setRank(int rank)
{
    UserDefault* userDefault = UserDefault::getInstance();
    userDefault->setIntegerForKey(Constant::UserDefaultKey::RANK(), rank);
}

void UserDataStore::setHighScore(std::vector<std::string> scoreList)
{
    UserDefault* userDefault = UserDefault::getInstance();

    // {
    //   1: {"chain":200, "score":12300},
    //   2: {"chain":200, "score":12300},
    //   3: {"chain":200, "score":12300},
    //   4: {"chain":200, "score":12300},
    //   5: {"chain":200, "score":12300},
    // }
    //
    picojson::value value;
    picojson::array detail_list;
    
    picojson::object detail;
    detail.insert(std::make_pair("chain", picojson::value(std::string("200"))));
    detail.insert(std::make_pair("score", picojson::value(std::string("12300"))));
    detail_list.push_back(picojson::value(detail));

    picojson::object detail2;
    detail2.insert(std::make_pair("chain", picojson::value(std::string("400"))));
    detail2.insert(std::make_pair("score", picojson::value(std::string("25000"))));
    detail_list.push_back(picojson::value(detail2));
    value = picojson::value(detail_list);
    CCLOG("%s", value.serialize().c_str());
    userDefault->setStringForKey("ranking", value.serialize());

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
}

std::string UserDataStore::getHighScore()
{
    UserDefault* userDefault = UserDefault::getInstance();

//    picojson::array list;
//    
//    picojson::object detail;
//    detail.insert(std::make_pair("chain", picojson::value(std::string("200"))));
//    detail.insert(std::make_pair("score", picojson::value(std::string("12300"))));
//    list.push_back(picojson::value(detail));
//    
//    picojson::object detail2;
//    detail2.insert(std::make_pair("chain", picojson::value(std::string("400"))));
//    detail2.insert(std::make_pair("score", picojson::value(std::string("25000"))));
//    list.push_back(picojson::value(detail2));
    std::string value = "";
    value = userDefault->getStringForKey("ranking", "");
    CCLOG("get: %s", value.c_str());

    return value;
}
