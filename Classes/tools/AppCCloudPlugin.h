//
// AppCCloudPlugin.h
//
// appC cloud Plugin Cocos2d-x
// Created by cayto inc.
//

#ifndef __AppCCloudPlugin__
#define __AppCCloudPlugin__

#include <string>

#include <vector>
#include "cocos2d.h"
#include "spine/Json.h"


USING_NS_CC;

using namespace std;

/**
 *  ver 2系はjsonがnamespace extension内にある。
 */
#if (COCOS2D_VERSION < 0x00030000)
using namespace extension;
#endif

#define LOGPARSED(X)
#define LOGJSON(X)

class IData
{
public:
    virtual void setMembers(Json* jsonObject) = 0;
};
/**
 *  LeaderBoardデータ格納クラス
 */
class LeaderBoardData : public IData
{
public:
    LeaderBoardData(const string&);
    LeaderBoardData(Json* jsonObj);
    LeaderBoardData(const LeaderBoardData&);
    string getId() const;
    void setId(const string& id);
    string getName() const;
    void setName(const string&);
    int getScore() const;
    void setScore(int score);
    float getTime() const;
    void setTime(float time);
    virtual void setMembers(Json*);
private:
    string _id;
    string _name;
    int _score;
    float _time;
};

/**
 *  DataStoreデータ格納クラス
 */
class DataStoreData : public IData
{
public:
    DataStoreData(const string&);
    DataStoreData(Json* jsonObj);
    DataStoreData(const DataStoreData& );
    string getKey() const;
    void setKey(const string& );
    string getText() const;
    void setText(const string&);
    int getVal() const;
    void setVal(int);
    virtual void setMembers(Json*);
private:
    string _key;
    string _text;
    int _val;
};

/**
 * アイテム格納クラス
 */
class PurchaseData: public IData
{
public:
    PurchaseData(const string&);
    PurchaseData(Json* jsonObj);
    PurchaseData(const PurchaseData& jsonObj);
    string getId() const;
    void setId(const string&);
    string getName() const;
    void setName(const string&);
    int getCount() const;
    void setCount(int);
    virtual void setMembers(Json*);
private:
    string _id;
    string _name;
    int _count;
};
void logJson(const string& );
void logParsed(const LeaderBoardData&);
void logParsed(const DataStoreData&);
void logParsed(const PurchaseData&);

// APIオプション
const static int API_AD = 0x00000000;
const static int API_GAMERS = 0x00000001;
const static int API_PUSH = 0x00000010;
const static int API_DATA = 0x00000100;
const static int API_PURCHASE = 0x00001000;
const static int API_REWARD = 0x00010000;

class AppCCloudPlugin
{
public:
    // 広告表示位置
    enum Vertical {
        TOP = 0,
        BOTTOM
    };
    // 広告表示位置
    enum Horizontal {
        LEFT = 0,
        CENTER,
        RIGHT
    };
    // リリースステータス
    enum appCReleaseStatus {
        ReleaseStatusInDevelopment = 0,
        ReleaseStatusInReview,
        ReleaseStatusReadyForSale
    };
private:
    static string mediaKey;
    static void* marqueeView;
    static void* simpleView;
    static void* moveIconView;
    static bool setup;
    static void* functionFlg;
    static bool appCCloudStartedFlag;
    static int options;
    static unsigned long appCFlags;
    
    AppCCloudPlugin();
    ~AppCCloudPlugin();
    static AppCCloudPlugin& getInstance();
public:
    static AppCCloudPlugin& setMK_iOS(const string& );
    static AppCCloudPlugin& setOptions(int);
    static bool start();
    static void finish();
    static int getReleaseStatus();
    
    class Ad
    {
    public:
        static void openAdListView();
        static void showSimpleView(Vertical, const string& = "", const string& = "");
        static void hideSimpleView();
        static void showMoveIconView(Horizontal, Vertical,const string& = "", const string& = "");
        static void hideMoveIconView();
        static void showMarqueeView(Vertical, const string& = "");
        static void hideMarqueeView();
        static void showCutin();
        static void showCutinFinish();
        static void showMatchAppView(Horizontal , Vertical );
        static void hideMatchAppView();
        static void hideAllAdViews();
        static bool isForegroundAd();
        static void showRecBannerView(Vertical);
        static void hideRecBannerView();
        static void showRecInterstitial();
        static void showRecInterstitialFinish();
    };
    class Data
    {
    public:
        static void setDataStore(const string& , const string&);
        static void setDataStore(const string& , int );
        static DataStoreData getDataStore(const string& );
    };
    class Gamers
    {
    public:
        static void incPlayCount();
        static int getPlayCount();
        static void setLeaderBoard(int, int);
        static void setLeaderBoard(int, float);
        static LeaderBoardData getLeaderBoard(int);
        static void showGamersView();
        static void setActiveLeaderBoards(vector<string>&);
    };
    class Purchase
    {
    public:
        static vector<PurchaseData> getAllData();
        static int getItemCount(const string&);
        static void setItemCount(const string&, int count);
        static void addItemCount(const string&, int count);
        static PurchaseData getItem(const string&);
        static void openPurchaseView();
        static void setActiveItems(const string&, vector<string>&);
    };
    class Reward
    {
    public:
        static void openRewardPointView();
        static void openRewardServiceViews(const string&);
        static bool isRewardService(const string&);
        static void rewardClearService(const string&);
        static void getService(const string&);
    };
};



/**
 *  配列
 *
 *  @param jsonstr        JSON文字列
 *  @param outputVector   結果格納先
 *  @param parseItemJson* 1要素をパースする関数へのポインタ
 *
 */
template<class T> static void parseArray(const string& jsonstr, vector<T>& outputVector )
{
    Json* jsonObj = Json_create(jsonstr.c_str());
    if(!jsonObj){
        return ;
    }
    if(!jsonObj->child){
        outputVector.push_back(T(jsonObj));
    }else{
        jsonObj = jsonObj->child;
        do{
            outputVector.push_back(T(jsonObj));
        }while( (jsonObj = jsonObj->next) != NULL);
    }
    Json_dispose(jsonObj);
    
    LOGJSON(jsonstr);
    
    long size = outputVector.size();
    for(long i = 0; i < size; i ++)
    {
        IData* data = dynamic_cast<IData*>(&outputVector[i]);
        if(data){
            LOGPARSED(*(T*)data);
        }
    }
    return ;
};

#endif
