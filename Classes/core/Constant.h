#ifndef __mikumoburst__Constant__
#define __mikumoburst__Constant__

#define BM_FONT_SIZE(__SIZE , __BASE) (CC_CONTENT_SCALE_FACTOR() * ((float)__SIZE / (float)__BASE))
#define BM_FONT_SIZE64(__SIZE) (BM_FONT_SIZE(__SIZE , 64))

class Constant
{
public:
    static const int GAME_TIME = 10;
    static const int MAX_UP_GAME_TIME = 5;
    static const int DEFAULT_ENEMY_HP = 100;
    static const int DEFAULT_ENEMY_BOSS_HP = 1000;
    static const int BASE_DAMAGE_NORMAL = 1;
    static const int BASE_DAMAGE_BURST = 4;
    static const int DAMAGE_RANK_UP_INCREMENT = 2;
    static const int HP_RANK_UP_INCREMENT = 10;
    static const int HP_RANK_UP_BOSS_INCREMENT = 100;
    static const int LIMIT_RANK = 999;
    static const int LIMIT_DAMAGE = 999999;
    static const int MAX_PLAYER_BP = 50;
    static const int BP_INCREMENT = 1;
    static const int MAX_BURST_TIME = 2;
    static const int BURST_GAME_TIME_INCREMENT = 1;
    
    typedef std::vector<std::string> StringVector;

    enum ImagePersona
    {
        PersonaSelect = 0,
        PersonaBattle,
    };
    static const std::map<ImagePersona, StringVector> PERSONA_IMAGE_LIST(){
        return {
            {ImagePersona::PersonaSelect, {
//                "chara_f316", "chara_f317",
                    "persona_conoha", "persona_anzu",
                }
            },
            {ImagePersona::PersonaBattle , {
                    "chara_f317",
                }
            },
        };
    };
    static const StringVector PERSONA_IMAGE_LIST(ImagePersona key){
        std::map<ImagePersona, StringVector> map = PERSONA_IMAGE_LIST();
        return map[key];
    }

    enum ImageEnemy
    {
        EnemyNormal = 0,
        EnemyBoss,
    };
    static const std::map<ImageEnemy, StringVector> ENEMY_IMAGE_LIST(){
        return {
            {ImageEnemy::EnemyNormal, {
//                    "f183", "f186", "f189", "f195", "f201", "f207", "f271", "f274",
                    "anpo_1", "anpo_2", "anpo_5", "bis", "dimetrodon_r", "dimetrodon_z",
                    "flying_cat", "heishi_2", "heishi_3", "heishi", "load_dark", "load",
                    "magic_black", "magic_white", "magic", "mino_2", "mino_3",
                    "necro", "onbonoyasu_1", "oni_r_1", "oni_r_2", "rev_1", "rev_2",
                    "ride_cat_ice", "ride_cat", "rion_l", "rion_r", "rion",
                }
            },
            {ImageEnemy::EnemyBoss , {
//                    "f277"
                    "Hecatoncheir_1L", "Hecatoncheir_2L", "Hecatoncheir_3L",
                }
            },
        };
    };
    static const StringVector ENEMY_IMAGE_LIST(ImageEnemy key){
        std::map<ImageEnemy, StringVector> map = ENEMY_IMAGE_LIST();
        return map[key];
    }

    static const std::vector<std::string> BG_IMAGE_LIST(){
        return {
            "000", "001", "002", "003", "004", "006", "007", "008", "010",
            "011", "012", "013"
        };
    };


    enum ImageEffect
    {
        ImageNormal = 0,// 通常攻撃
        ImageBurst,     // バーストタイム
        ImageBurstSub,  // バーストタイム（サブエフェクト）
    };
    static const std::map<ImageEffect, StringVector> BATTLE_EFFECT_IMAGE_LIST(){
        return {
//            {ImageEffect::ImageNormal, {"battleEffect107a", "battleEffect107b"}},
//            {ImageEffect::ImageBurst , {
//                    "battleEffect107c", "battleEffect107d", "battleEffect107e",
//                    "battleEffect107f", "battleEffect107g", "battleEffect107h",
//                    "battleEffect107i", "battleEffect107j"
//                }
//            },
            {ImageEffect::ImageNormal  , {"ef22", "ef24", "ef25"}},
            {ImageEffect::ImageBurst   , {"ef02", "ef07", "ef09", "ef20", "ef31-2", "ef32"}},
            {ImageEffect::ImageBurstSub, {"ef16", "ef17"}}
        };
    };
    static const StringVector BATTLE_EFFECT_IMAGE_LIST(ImageEffect key){
        std::map<ImageEffect, StringVector> map = BATTLE_EFFECT_IMAGE_LIST();
        return map[key];
    }
    enum SoundEffect
    {
        SoundNormal = 0,// 通常攻撃
        SoundBurst,     // バーストタイム
    };
    static const std::map<SoundEffect, StringVector> EFFECT_LIST(){
        return {
            {SoundEffect::SoundNormal, {"se_battle_blow", "se_battle_gun"}},
            {SoundEffect::SoundBurst , {"se_battle_darkness", "se_battle_fire", "se_battle_water"}},
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
        BurstAttack,    // バーストタイム
        BattleEnd,      // バトル終了
        EnemyDefeat,    // 敵撃破
    };
    static const std::map<Voice, StringVector> VOICE_LIST(){
        return {
            {Voice::Ready       , {"i01", "i30"}},
            {Voice::NormalAttack, {"i02", "i03", "i04","i05"}},
            {Voice::BurstAttack , {"i06", "i14", "i27"}},
            {Voice::BattleEnd   , {"i10", "i11", "i12"}},
            {Voice::EnemyDefeat , {"i24", "i25"}},
        };
    };
    static const StringVector VOICE_LIST(Voice key){
        std::map<Voice, StringVector> map = VOICE_LIST();
        return map[key];
    }

    static const char* APPC_MEDIA_KEY(){return "DumyMediaKey";}
    static const int LEADERBOARD_BATTLE_COUNT = 1237;
    static const int LEADERBOARD_BATTLE_RANK = 1238;
    static const int LEADERBOARD_TOTAL_SCORE = 1239;
    static const int LEADERBOARD_TOTAL_BURST = 1240;
    
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
        static const char* TOTAL_HIT(){return "total_hit";}
        static const char* TOTAL_BURST(){return "total_burst";}
//        static const char* SCORE_TABLE(){return "score_table";}
//        static const char* SCORE_TABLE_RANK(){return "score_table_rank";}
//        static const char* SCORE_TABLE_SCORE(){return "score_table_score";}
//        static const char* SCORE_TABLE_BURST(){return "score_table_burst";}
    };
};

#endif /* defined(__mikumoburst__Constant__) */
