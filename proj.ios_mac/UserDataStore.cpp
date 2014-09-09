#include "UserDataStore.h"
#include "Constant.h"

USING_NS_CC;
using namespace std;

UserDataStore::UserDataStore()
{
    
}

UserDataStore::~UserDataStore()
{
    
}

int UserDataStore::getData()
{
    int ret = this->userDefault->getIntegerForKey(Constant::UserDefaultKey::RANK(), 1);
    return ret;
}
