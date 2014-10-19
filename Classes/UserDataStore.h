#ifndef __Fragment_of_Eternity__UserDataStore__
#define __Fragment_of_Eternity__UserDataStore__

#include "cocos2d.h"

USING_NS_CC;

class UserDataStore
{
private:
    UserDataStore();
    
public:
    static void setRank(int rank);
    static int getRank(int defaultRank = NULL);
    
    static void setHighScore(std::vector<std::map<std::string, std::string>> scoreList);
    static std::vector<std::map<std::string, std::string>> getHighScore();
    
private:
    void initialize();
};

#endif /* defined(__Fragment_of_Eternity__UserDataStore__) */
