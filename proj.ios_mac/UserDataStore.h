#ifndef __Fragment_of_Eternity__UserDataStore__
#define __Fragment_of_Eternity__UserDataStore__

#include "cocos2d.h"

USING_NS_CC;

class UserDataStore
{
    
public:
    UserDataStore();
    virtual ~UserDataStore();
    
    UserDefault* userDefault = UserDefault::getInstance();
    int getData();

protected:
    
private:

};

#endif /* defined(__Fragment_of_Eternity__UserDataStore__) */
