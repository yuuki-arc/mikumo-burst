#include "UserDataStore.h"
#include "Constant.h"

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
