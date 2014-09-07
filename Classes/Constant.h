#ifndef __Fragment_of_Eternity__Constant__
#define __Fragment_of_Eternity__Constant__

class Constant
{
public:
    static const int DEFAULT_ENEMY_HP = 100000;
    static const int LIMIT_RANK = 99;
    static const int LIMIT_DAMAGE = 999999;
    
    class UserDefaultKey
    {
    public:
        static const char* RANK(){return "rank";}
    };
};

#endif /* defined(__Fragment_of_Eternity__Constant__) */
