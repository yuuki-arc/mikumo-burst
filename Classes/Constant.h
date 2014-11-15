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
    
    static const std::vector<std::string> PERSONA_IMAGE_LIST(){
        return {
            "chara_f316", "chara_f317",
        };
    };

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

    typedef std::vector<std::string> StringVector;

    enum ImageEffect
    {
        ImageNormal = 0,// 通常攻撃
        ImageBreak,     // 限界突破
    };
    static const std::map<ImageEffect, StringVector> BATTLE_EFFECT_IMAGE_LIST(){
        return {
            {ImageEffect::ImageNormal, {"battleEffect107a", "battleEffect107b"}},
            {ImageEffect::ImageBreak , {
                    "battleEffect107c", "battleEffect107d", "battleEffect107e",
                    "battleEffect107f", "battleEffect107g", "battleEffect107h",
                    "battleEffect107i", "battleEffect107j"
                }
            },
        };
    };
    static const StringVector BATTLE_EFFECT_IMAGE_LIST(ImageEffect key){
        std::map<ImageEffect, StringVector> map = BATTLE_EFFECT_IMAGE_LIST();
        return map[key];
    }
    enum SoundEffect
    {
        SoundNormal = 0,// 通常攻撃
        SoundBreak,     // 限界突破
    };
    static const std::map<SoundEffect, StringVector> EFFECT_LIST(){
        return {
            {SoundEffect::SoundNormal, {"se_battle_blow", "se_battle_gun"}},
            {SoundEffect::SoundBreak , {"se_battle_darkness", "se_battle_fire", "se_battle_water"}},
        };
    };
    static const StringVector EFFECT_LIST(SoundEffect key){
        std::map<SoundEffect, StringVector> map = EFFECT_LIST();
        return map[key];
    }
    enum Voice
    {
        Ready = 0,      // 準備完了
        NormalAttack,   // 通常攻撃
        BreakAttack,    // 限界突破
        BattleEnd,      // バトル終了
        EnemyDefeat,    // 敵撃破
    };
    static const std::map<Voice, StringVector> VOICE_LIST(){
        return {
            {Voice::Ready       , {"i01", "i30"}},
            {Voice::NormalAttack, {"i02", "i03", "i04","i05"}},
            {Voice::BreakAttack , {"i06", "i14", "i27"}},
            {Voice::BattleEnd   , {"i10", "i11", "i12"}},
            {Voice::EnemyDefeat , {"i24", "i25"}},
        };
    };
    static const StringVector VOICE_LIST(Voice key){
        std::map<Voice, StringVector> map = VOICE_LIST();
        return map[key];
    }

    static const char* APPC_MEDIA_KEY(){return "DumyMediaKey";}
    static const char* NORMAL_FONT(){return "normal.fnt";}
    static const char* LARGE_FONT(){return "large.fnt";}

    /**
     *  UserDefaultのキー
     */
    class UserDefaultKey
    {
    public:
        static const char* DATA_STORED(){return "data_stored";}
        static const char* BATTLE_COUNT(){return "battle_count";}
        static const char* RANK(){return "rank";}
        static const char* HIGH_RANK(){return "high_rank";}
        static const char* TOTAL_SCORE(){return "total_score";}
        static const char* TOTAL_BREAK(){return "total_break";}
        static const char* SCORE_TABLE(){return "score_table";}
        static const char* SCORE_TABLE_RANK(){return "score_table_rank";}
        static const char* SCORE_TABLE_SCORE(){return "score_table_score";}
        static const char* SCORE_TABLE_BREAK(){return "score_table_break";}
    };
};

#endif /* defined(__Fragment_of_Eternity__Constant__) */
