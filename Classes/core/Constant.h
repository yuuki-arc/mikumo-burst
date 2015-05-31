#ifndef __mikumoburst__Constant__
#define __mikumoburst__Constant__

#include "core/DefineParameters.h"

#define BM_FONT_SIZE(__SIZE , __BASE) (CC_CONTENT_SCALE_FACTOR() * ((float)__SIZE / (float)__BASE))
#define BM_FONT_SIZE64(__SIZE) (BM_FONT_SIZE(__SIZE , 64))

#include<utility>

template<class Derived>
struct create_func {
    template<class... Args>
    static Derived* create(Args&&... args) {
        auto p = new Derived();
        if (p->init(std::forward<Args>(args)...)) {
            p->autorelease();
            return p;
        } else {
            delete p;
            return nullptr;
        }
    }
};

class Constant
{
public:
    static const int GAME_TIME = 10;
    static const int MAX_UP_GAME_TIME = 5;
    static const int DEFAULT_ENEMY_HP = 900;
    static const int DEFAULT_ENEMY_BOSS_HP = 10000;
    static const int BASE_DAMAGE_NORMAL = 10;
    static const int BASE_DAMAGE_BURST = 15;
//    static const int DAMAGE_RANK_UP_INCREMENT = 2;
    static const int HP_RANK_5_UP_INCREMENT = 50;
    static const int HP_RANK_5_UP_BOSS_INCREMENT = 50;
    static const int LIMIT_RANK = 999;
    static const int LIMIT_SCORE = 2000000000;  // int型上限 2147483647（GAMERSはint型のみ）
//    static const int LIMIT_DAMAGE = 999999;
    static const int MAX_PLAYER_BP = 500;
    static const int BP_INCREMENT = 10;
    static const int MAX_BURST_TIME = 2;
    static const int BURST_GAME_TIME_INCREMENT = 1;
    
    typedef std::vector<std::string> StringVector;

    enum CharaSelect {
        Conoha = 0,                 // 通常バトル（このは）
        Anzu = 1,                   // 通常バトル（あんず）
        VsBoss = 2,                 // ボスバトル
        CharaSelectStart = Conoha,  // ループ用
        CharaSelectEnd = Anzu,      // ループ用
    };
    static const char* charaKey(CharaSelect charaSelect){
        switch (charaSelect){
            case Conoha: return "conoha"; break;
            case Anzu:   return "anzu";   break;
            default:     return "";       break;
        }
    };
    static const char* charaName(CharaSelect charaSelect){
        switch (charaSelect){
            case Conoha: return "このは"; break;
            case Anzu:   return "あんず"; break;
            default:     return "このは＆あんず"; break;
        }
    };
    
    enum ImagePersona
    {
        PersonaSelect = 0,  // 選択画面
        PersonaIcon,        // キャラクターアイコン
        PersonaBattle1,     // 戦闘カットインver.1
        PersonaBattle2,     // 戦闘カットインver.2
        PersonaBattle3,     // 戦闘カットイン最終
        PersonaStory,       // ストーリー用
    };
    static const std::map<ImagePersona, StringVector> PERSONA_IMAGE_LIST(){
        return {
            {ImagePersona::PersonaSelect , {"persona_conoha", "persona_anzu", ""}},
            {ImagePersona::PersonaIcon   , {"icon_conoha"   , "icon_anzu"   , "icon_anco"}},
            {ImagePersona::PersonaBattle1, {"cutin_conoha1" , "cutin_anzu1" , "cutin_conoha1"}},
            {ImagePersona::PersonaBattle2, {"cutin_conoha2" , "cutin_anzu2" , "cutin_anzu2"}},
            {ImagePersona::PersonaBattle3, {"cutin_anco"    , "cutin_anco"  , "cutin_anco"}},
            {ImagePersona::PersonaStory  , {"persona_conoha", "persona_anzu", "Hecatoncheir_3L"}},
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
                    "anpo_1", "anpo_2", "anpo_5", "bis", "dimetrodon_r", "dimetrodon_z",
                    "heishi_2", "heishi_3", "heishi", "load_dark", "load",
                    "magic_black", "magic_white", "magic", "mino_2", "mino_3",
                    "necro", "rev_1", "rev_2",
//                    "ride_cat_ice", "ride_cat", "flying_cat", "onbonoyasu_1", "rion_l", "rion_r", "rion",
                }
            },
            {ImageEnemy::EnemyBoss , {
//                    "Hecatoncheir_1L", "Hecatoncheir_2L", "Hecatoncheir_3L",
                    "Hecatoncheir_3L",
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
            "000", "001", "006", "007", "008", "011", "012"
        };
    };


    enum ImageEffect
    {
        ImageNormal = 0,// 通常攻撃
        ImageBurst,     // バーストタイム
//        ImageBurstSub,  // バーストタイム（サブエフェクト）
    };
    static const std::map<ImageEffect, StringVector> BATTLE_EFFECT_IMAGE_LIST(){
        return {
            {ImageEffect::ImageNormal  , {"ef22", "ef24", "ef25"}},
            {ImageEffect::ImageBurst   , {"ef02", "ef07", "ef09", "ef20", "ef31-2", "ef32"}},
//            {ImageEffect::ImageBurstSub, {"ef16", "ef17"}}
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
        Select = 0,     // キャラ選択
        Ready,          // 準備完了
        NormalAttack,   // 通常攻撃
        BurstAttack,    // バーストタイム
        BattleEnd,      // バトル終了
        EnemyDefeat,    // 敵撃破
    };
    static const std::map<Voice, StringVector> VOICE_LIST(CharaSelect charaSelect){
        switch (charaSelect){
            case Conoha:
                return {
                    {Voice::Select      , {"i18", "i34"}},
                    {Voice::Ready       , {"i01", "i30"}},
                    {Voice::NormalAttack, {"i02", "i03", "i04","i05"}},
                    {Voice::BurstAttack , {"i06", "i14", "i27"}},
                    {Voice::BattleEnd   , {"i10", "i11", "i12"}},
                    {Voice::EnemyDefeat , {"i24", "i25"}},
                };
                break;
            case Anzu:
                return {
                    {Voice::Select      , {"u16", "u19"}},
                    {Voice::Ready       , {"u26", "u28"}},
                    {Voice::NormalAttack, {"u02", "u03", "u04","u05"}},
                    {Voice::BurstAttack , {"u01", "u25", "u32"}},
                    {Voice::BattleEnd   , {"u20", "u27", "u31"}},
                    {Voice::EnemyDefeat , {"u24", "u36"}},
                };
                break;
            default:
                return {
                    {Voice::Select      , {"i18", "i34"}},
                    {Voice::Ready       , {"i01", "i30"}},
                    {Voice::NormalAttack, {"i02", "i03", "i04","i05"}},
                    {Voice::BurstAttack , {"i06", "i14", "i27"}},
                    {Voice::BattleEnd   , {"i10", "i11", "i12"}},
                    {Voice::EnemyDefeat , {"i24", "i25"}},
                };
                break;
        }
    };
    static const StringVector VOICE_LIST(CharaSelect charaSelect, Voice key){
        std::map<Voice, StringVector> map = VOICE_LIST(charaSelect);
        return map[key];
    }
    
    static const char* CACHE_FILE_APPS(){return "00_apps";}
    static const char* CACHE_FILE_STORY(){return "10_scenario";}

    static const char* SHEET_NAME_AP_APPS(){return "apps";}
    static const char* SHEET_NAME_AP_SCENARIO(){return "scenario";}

    static const char* SHEET_COLUMN_AP_APPS(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        return "ios";
#else
        return "android";
#endif
    }

#ifdef __mikumoburst__DefineParameters__
    static const char* APPC_MEDIA_KEY(){return __APPC_MEDIA_KEY;}
    static const int LEADERBOARD_BATTLE_COUNT = __LEADERBOARD_BATTLE_COUNT;
    static const int LEADERBOARD_TOTAL_RANK   = __LEADERBOARD_TOTAL_RANK;
    static const int LEADERBOARD_TOTAL_TAP    = __LEADERBOARD_TOTAL_TAP;
    static const int LEADERBOARD_TOTAL_BURST  = __LEADERBOARD_TOTAL_BURST;
    static const int LEADERBOARD_TOTAL_SCORE  = __LEADERBOARD_TOTAL_SCORE;
    static const int LEADERBOARD_RANK_CONOHA  = __LEADERBOARD_RANK_CONOHA;
    static const int LEADERBOARD_RANK_ANZU    = __LEADERBOARD_RANK_ANZU;
#else
    static const char* APPC_MEDIA_KEY(){return "dummy_media_key";}
    static const int LEADERBOARD_BATTLE_COUNT = 1;
    static const int LEADERBOARD_TOTAL_RANK   = 2;
    static const int LEADERBOARD_TOTAL_TAP    = 3;
    static const int LEADERBOARD_TOTAL_SCORE  = 4;
    static const int LEADERBOARD_TOTAL_BURST  = 5;
    static const int LEADERBOARD_RANK_CONOHA  = 6;
    static const int LEADERBOARD_RANK_ANZU    = 7;
#endif
    
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
        static const char* TOTAL_RANK(){return "total_rank";}
        static const char* RANK_LIST(){return "rank_list";}
        static const char* TOTAL_SCORE(){return "total_score";}
        static const char* TOTAL_TAP(){return "total_tap";}
        static const char* TOTAL_BURST(){return "total_burst";}
    };
    
    static const char* TWEET_TEXT_TEMPLATE(){
        return "%s【ランク %d｜タップ %d 回｜バースト %d 回｜スコア %d pt】 http://yuukiar.co/apps/mikumo-burst/ #みくもバースト！ #マスコットアプリ文化祭";
    }
};

#endif /* defined(__mikumoburst__Constant__) */
