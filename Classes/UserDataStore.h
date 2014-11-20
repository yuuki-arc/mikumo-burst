#ifndef __10sec_BURST__UserDataStore__
#define __10sec_BURST__UserDataStore__

#include "cocos2d.h"

USING_NS_CC;

typedef std::map<std::string, std::string> StringMap;
typedef std::vector<StringMap> StringMapVector;

class UserDataStore
{
private:
    UserDataStore();
    static UserDataStore* instance;
    UserDefault* userDefault;
    void initialize();
    
public:
    static UserDataStore* getInstance();

    void setupData();
    
    void setDataStoredOn();
    bool isDataStored();

    void setBattleCount(int value);
    int getBattleCount();
    
    void setRank(int value);
    int getRank();

    void setHighRank(int value);
    int getHighRank();

    void setTotalScore(int value);
    int getTotalScore();

    void setTotalBreak(int value);
    int getTotalBurst();
    
    void setScoreTable(StringMapVector scoreList);
    StringMapVector getScoreTable();
    
};

#endif /* defined(__10sec_BURST__UserDataStore__) */
