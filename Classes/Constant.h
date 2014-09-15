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
        static const char* RANKING(){return "ranking";}
    };
    
    static const std::vector<std::string> ENEMY_IMAGE_LIST(){return {"f183", "f186", "f189", "f195", "f201", "f207", "f271", "f274", "f277"};};
    static const std::vector<std::string> BG_IMAGE_LIST(){return {"000", "001", "002", "003", "004", "006", "007", "008", "010", "011", "012", "013"};};
    static const std::vector<std::string> BATTLE_EFFECT_IMAGE_LIST(){return {"battleEffect107a", "battleEffect107b", "battleEffect107c", "battleEffect107d", "battleEffect107e", "battleEffect107f", "battleEffect107g", "battleEffect107h", "battleEffect107i", "battleEffect107j"};};
    static const std::vector<std::string> EFFECT_LIST(){return {"se_battle_blow", "se_battle_darkness", "se_battle_fire", "se_battle_gun", "se_battle_water"};};
};

#endif /* defined(__Fragment_of_Eternity__Constant__) */
