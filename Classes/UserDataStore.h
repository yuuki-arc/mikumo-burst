#ifndef __Fragment_of_Eternity__UserDataStore__
#define __Fragment_of_Eternity__UserDataStore__

#include "cocos2d.h"

USING_NS_CC;

typedef std::map<std::string, std::string> StringMap;
typedef std::vector<StringMap> StringMapVector;

class UserDataStore
{
private:
    UserDataStore();
    static UserDataStore* instance;
    void initialize();
    
public:
    static UserDataStore* getInstance();

    void setupData();
    
    void setDataStoredOn();
    bool isDataStored();
    
    void setRank(int rank);
    int getRank(int defaultRank = NULL);
    
    void setHighScore(StringMapVector scoreList);
    StringMapVector getHighScore();
    
};

#endif /* defined(__Fragment_of_Eternity__UserDataStore__) */
