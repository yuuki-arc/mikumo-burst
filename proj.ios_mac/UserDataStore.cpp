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

//int UserDataStore::getData()
//{
//    int ret = this->userDefault->getIntegerForKey(Constant::UserDefaultKey::RANK(), 1);
//    return ret;
//}

template <class Type>
Type UserDataStore::getData(Type key)
{
    Type ret = NULL;
    if (typeid(Type) == typeid(int))
    {
        ret = this->userDefault->getIntegerForKey(Constant::UserDefaultKey::RANK(), 1);
    }
    return ret;
}

void sub(int a);
void sub(char a);
