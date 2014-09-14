#ifndef __Fragment_of_Eternity__UserDataStore__
#define __Fragment_of_Eternity__UserDataStore__

#include "cocos2d.h"

USING_NS_CC;

class UserDataStore
{
private:
    UserDataStore();
    
public:
    static int getRank(int defaultRank = NULL);
    static void setRank(int rank);
    
    static std::string getHighScore();
    static void setHighScore(std::vector<std::string> scoreList);
    
private:
    void initialize();
};

#endif /* defined(__Fragment_of_Eternity__UserDataStore__) */
