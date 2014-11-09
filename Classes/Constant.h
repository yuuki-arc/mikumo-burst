#ifndef __Fragment_of_Eternity__Constant__
#define __Fragment_of_Eternity__Constant__

#define BM_FONT_SIZE(__SIZE , __BASE) (CC_CONTENT_SCALE_FACTOR() * ((float)__SIZE / (float)__BASE))
#define BM_FONT_SIZE64(__SIZE) (BM_FONT_SIZE(__SIZE , 64))

class Constant
{
public:
    static const int GAME_TIME = 10;
    static const int ETERNITY_BREAK_TIME = 3;
    static const int DEFAULT_ENEMY_HP = 1000000;
    static const int BASE_DAMAGE = 1000;
    static const int BASE_DAMAGE_BREAK = 4000;
    static const int DAMAGE_RANK_UP_INCREMENT = 1000;
    static const int HP_RANK_UP_INCREMENT = 100000;
    static const int LIMIT_RANK = 999;
    static const int LIMIT_DAMAGE = 999999;
    static const int MAX_PLAYER_EP = 100;
    static const int EP_INCREMENT = 1;
    
    static const std::vector<std::string> ENEMY_IMAGE_LIST(){
        return {
            "f183", "f186", "f189", "f195", "f201", "f207", "f271", "f274",
            "f277"
        };
    };
    static const std::vector<std::string> BG_IMAGE_LIST(){
        return {
            "000", "001", "002", "003", "004", "006", "007", "008", "010",
            "011", "012", "013"
        };
    };
    static const std::vector<std::string> BATTLE_EFFECT_IMAGE_LIST(){
        return {
            "battleEffect107a", "battleEffect107b", "battleEffect107c",
            "battleEffect107d", "battleEffect107e", "battleEffect107f",
            "battleEffect107g", "battleEffect107h", "battleEffect107i",
            "battleEffect107j"
        };
    };
    static const std::vector<std::string> EFFECT_LIST(){
        return {
            "se_battle_blow", "se_battle_gun",
            "se_battle_darkness", "se_battle_fire", "se_battle_water"
        };
    };

    /**
     *  UserDefaultのキー
     */
    class UserDefaultKey
    {
    public:
        static const char* DATA_STORED(){return "data_stored";}
        static const char* RANK(){return "rank";}
        static const char* HIGH_SCORE(){return "high_score";}
        static const char* HIGH_CHAIN(){return "high_chain";}
        static const char* RANKING(){return "ranking";}
    };
};

#endif /* defined(__Fragment_of_Eternity__Constant__) */
