#ifndef __Fragment_of_Eternity__Constant__
#define __Fragment_of_Eternity__Constant__

#define BM_FONT_SIZE(__SIZE , __BASE) (CC_CONTENT_SCALE_FACTOR() * ((float)__SIZE / (float)__BASE))
#define BM_FONT_SIZE64(__SIZE) (BM_FONT_SIZE(__SIZE , 64))

class Constant
{
public:
    static const int GAME_TIME = 60;
    static const int DEFAULT_ENEMY_HP = 100000;
    static const int BASE_DAMAGE = 10000;
    static const int LIMIT_RANK = 99;
    static const int LIMIT_DAMAGE = 999999;
    
    class UserDefaultKey
    {
    public:
        static const char* RANK(){return "rank";}
        static const char* HIGH_SCORE(){return "high_score";}
        static const char* HIGH_CHAIN(){return "high_chain";}
    };
};

#endif /* defined(__Fragment_of_Eternity__Constant__) */
