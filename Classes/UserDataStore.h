#ifndef __Fragment_of_Eternity__UserDataStore__
#define __Fragment_of_Eternity__UserDataStore__

#include "cocos2d.h"

USING_NS_CC;

typedef std::map<std::string, std::string> StringMap;
typedef std::vector<StringMap> StringMapVector;

class UserDataStore : public UserDefault
{
private:
    UserDataStore();
    virtual ~UserDataStore();
    
public:
    static void setRank(int rank);
    static int getRank(int defaultRank = NULL);
    
    static void setHighScore(StringMapVector scoreList);
    static StringMapVector getHighScore();
    
};

#endif /* defined(__Fragment_of_Eternity__UserDataStore__) */
