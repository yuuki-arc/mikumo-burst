#ifndef __mikumoburst__UserDataStore__
#define __mikumoburst__UserDataStore__

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
    StringMapVector getDefaultRankList();
    
    void setDataStoredOn();
    bool isDataStored();

    void setBattleCount(int value);
    int getBattleCount();
    
    void setRankList(StringMapVector rankList);
    StringMapVector getRankList();

    void setTotalRank(int value);
    int getTotalRank();
    
    void setTotalScore(int value);
    int getTotalScore();

    void setTotalTap(int value);
    int getTotalTap();
    
    void setTotalBurst(int value);
    int getTotalBurst();
    
//    void setScoreTable(StringMapVector scoreList);
//    StringMapVector getScoreTable();
    
};

#endif /* defined(__mikumoburst__UserDataStore__) */
