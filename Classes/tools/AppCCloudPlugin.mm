//
// AppCCloudPlugin.mm
//
// appC cloud Plugin Cocos2d-x
// Created by cayto inc.
//


#include "tools/AppCCloudPlugin.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "appCCloud.h"
//
#include "appCDefine.h"
#include "appCCloudDefine.h"

static UIView* getRootView();
static UIViewController* getViewController();
static appCHorizontal cnvAppCHorizontal(AppCCloudPlugin::Horizontal);
static appCVertical cnvAppCVertical(AppCCloudPlugin::Vertical);
static NSString* cnvStringgToNSString(const string& );
static string cnvNSStringToString(NSString* );
static string _purchaseGetJsonItem(const string& key);
static NSMutableArray *arrServiceId= [[NSMutableArray alloc] init];

int AppCCloudPlugin::options = 0;
void* AppCCloudPlugin::simpleView = NULL;
void* AppCCloudPlugin::moveIconView = NULL;
void* AppCCloudPlugin::marqueeView = NULL;
string AppCCloudPlugin::mediaKey = "";
bool AppCCloudPlugin::appCCloudStartedFlag = false;
unsigned long AppCCloudPlugin::appCFlags = (unsigned long)0x00;

@interface AppCCloudPluginDelegate : NSObject<appCDelegate>
@property (nonatomic,readonly) bool resultStartup;
@property (nonatomic, readonly) bool setup;
@end
/**
 *　appCDelegateインプリメントクラス
 */
@implementation AppCCloudPluginDelegate{
    
    NSCondition*  conditionToWaitStart;
}
/**
 *  初期化
 *
 *  @return id
 */
-(id)init
{
    self = [super init];
    if(self)
    {
        conditionToWaitStart = [[[NSCondition alloc]init]autorelease];
        self->_resultStartup = NO;
        self->_setup = NO;
    }
    return self;
}

/**
 * @brief setupAppCWithMediaKey の完了通知
 *
 * @param succeed 成功・失敗フラグ
 */
- (void)finishedSetupAppC:(BOOL)succeed
{
    self->_resultStartup = succeed;
    self->_setup = YES;
}

@end

static AppCCloudPluginDelegate* appCCloudDelegate = [[AppCCloudPluginDelegate alloc] init];

/**
 *  コンストラクタ
 */
AppCCloudPlugin::AppCCloudPlugin()
{
}

/**
 *  デストラクタ
 */
AppCCloudPlugin::~AppCCloudPlugin()
{
}

/**
 * インスタンス取得
 */
AppCCloudPlugin& AppCCloudPlugin::getInstance()
{
    static AppCCloudPlugin instance;
    return instance;
}


/**
 *  メディアキーの設定
 *  iOSのみ有効
 *  AndroidはAndroidManifest.xmlへメディアキーを記述してください
 *
 *  @param mk メディアキー
 *  @return プラグインのインスタンス
 */
AppCCloudPlugin& AppCCloudPlugin::setMK_iOS(const string& mk)
{
    mediaKey = mk;
    return getInstance();
}

/**
 *  オプションの設定
 *
 *  @param options_ 使用するオプション
 *
 *  @return AppCCloudPlugin
 */
AppCCloudPlugin& AppCCloudPlugin::setOptions(int options_)
{
    options = options_;
    return getInstance();
}

/**
 *  appCCloundPlugin開始
 */
bool  AppCCloudPlugin::start()
{
    [appCCloud setDelegate:appCCloudDelegate];
    NSString *mk = cnvStringgToNSString(mediaKey);

    [appCCloud setupAppCWithMediaKey:mk option:(unsigned long)options];
    
    int count = 0;
    while ([appCCloudDelegate setup] == NO) {
        [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:0.5]];
        count ++;
        // loop until 0.5sec * 30 = 15sec
        if (count >= 30) {
            break;
        }
    }
    if( (options | API_GAMERS) != 0)
    {
        [appCCloud gamersStartGame];
    }

    bool setupResult = [appCCloudDelegate resultStartup];
    
    return setupResult;
}

/**
 *  プラグイン終了 (iOSはNOP）
 */
 void AppCCloudPlugin::finish()
{
}

/**
 *  リリースステータス取得
 *
 *  @return リリース状態
 */
int AppCCloudPlugin::getReleaseStatus()
{
    return [appCCloud getReleaseStatus];
}

/**
 *  広告リスト型表示
 */
void AppCCloudPlugin::Ad::openAdListView()
{
    [appCCloud openWebView];
}

/**
 *  シンプル型表示
 *
 *  @param vertical  表示縦位置
 *  @param skinColor スキンカラー(iOSは無効、Androidのみ有効)
 *  @param textColor テキストカラー(iOSは無効、Androidのみ有効)
 */
void AppCCloudPlugin::Ad::showSimpleView(Vertical vertical, const string& skinColor, const string& textColor)
{
    hideSimpleView();
    UIView *rootView = getRootView();
    UIViewController *viewController = getViewController();
    simpleView = [[[appCSimpleView alloc] initWithViewController:viewController vertical:cnvAppCVertical(vertical)] autorelease];
    [rootView addSubview:(id)simpleView];
}

/**
 *  シンプル型非表示
 */
void AppCCloudPlugin::Ad::hideSimpleView()
{
    if (simpleView != nil) {
        [(id)simpleView removeFromSuperview];
        simpleView = nil;
    }
}

/**
 *  ムーヴアイコン型表示
 *
 *  @param AppCCloudPlugin::horizontal 表示横位置
 *  @param AppCCloudPlugin::vertical   表示縦位置
 *  @param skinColor  スキンカラー(iOSは無効、Androidのみ有効)
 *  @param textColor  テキストカラー(iOSは無効、Androidのみ有効)
 */
void AppCCloudPlugin::Ad::showMoveIconView(Horizontal horizontal, Vertical vertical, const string& skinColor, const string& textColor)
{
    hideMoveIconView();
    UIView *rootView = getRootView();
    UIViewController *viewController = getViewController();
    moveIconView = [[[appCMoveIconView alloc] initWithViewController:viewController
                                                          horizontal:cnvAppCHorizontal(horizontal)
                                                            vertical:cnvAppCVertical(vertical)] autorelease];
    [rootView addSubview:(id)moveIconView];
}

/**
 *  ムーヴアイコン型非表示
 */
void AppCCloudPlugin::Ad::hideMoveIconView()
{
    if (moveIconView != nil) {
        [(id)moveIconView removeFromSuperview];;
        moveIconView = nil;
    }
}

/**
 *  マーキー型表示
 *
 *  @param vertical  表示縦位置
 *  @param color テキストカラー(iOSは無効、Androidのみ有効)
 */
void AppCCloudPlugin::Ad::showMarqueeView(Vertical vertical, const string& textColor)
{
    hideMarqueeView();
    UIView *rootView = getRootView();
    UIViewController *viewController =getViewController();
    marqueeView = [[[appCMarqueeView alloc] initWithViewController:viewController vertical:cnvAppCVertical(vertical)] autorelease];
    [rootView addSubview:(id)marqueeView];
}

/**
 *  マーキー型非表示
 */
void AppCCloudPlugin::Ad::hideMarqueeView()
{
    if (marqueeView != nil) {
        [(id)marqueeView removeFromSuperview];
        marqueeView = nil;
    }
}

/**
 *  カットイン型表示
 */
void AppCCloudPlugin::Ad::showCutin()
{
    UIView *rootView = getRootView();
    UIViewController *viewController = getViewController();
    __block appCCutinView* cutin = [[[appCCutinView alloc]
                                     initWithViewController:viewController
                                     closeBlock:^(id sender_)
                                     {
                                         [cutin removeFromSuperview];
                                     }] autorelease];
    [rootView addSubview:cutin];
}
/**
 *  カットイン型表示(iOSは無効です）
 *
 */
void AppCCloudPlugin::Ad::showCutinFinish()
{
}
/**
 *  マッチアップ表示(バナー)
 *
 *  @param AppCCloudPlugin::horizontal 表示横位置
 *  @param AppCCloudPlugin::vertical 表示縦位置
 */
void AppCCloudPlugin::Ad::showMatchAppView(AppCCloudPlugin::Horizontal horizontal, AppCCloudPlugin::Vertical vertical)
{
    [appCCloud matchAppShowBannerWithHorizontal:cnvAppCHorizontal(horizontal) vertical:cnvAppCVertical(vertical)];
}

/**
 *  マッチアップ非表示(バナー)
 */
void AppCCloudPlugin::Ad::hideMatchAppView()
{
    [appCCloud matchAppHideBanner];
}

/**
 *  リコネクトバナー表示(iOSは無効です）
 *
 */
void AppCCloudPlugin::Ad::showRecBannerView(AppCCloudPlugin::Vertical vertical)
{
}

/**
 *  リコネクトバナー非表示(iOSは無効です）
 *
 */
void AppCCloudPlugin::Ad::hideRecBannerView()
{
}

/**
 *  リコネクトインタースティシャル表示(iOSは無効です）
 *
 */
void AppCCloudPlugin::Ad::showRecInterstitial()
{
}

/**
 *  リコネクトインタースティシャル(終了)表示(iOSは無効です）
 *
 */
void AppCCloudPlugin::Ad::showRecInterstitialFinish()
{
}

/**
 *  全広告非表示
 */
void AppCCloudPlugin::Ad::hideAllAdViews()
{
    hideSimpleView();
    hideMoveIconView();
    hideMarqueeView();
    hideMatchAppView();
    hideRecBannerView();
}

/**
 *  広告前面確認.
 *
 *  @return true:前面　false:後面
 */
bool AppCCloudPlugin::Ad::isForegroundAd()
{
    return (int)(
                 [appCCloud showingWebView]
                 ||
                 [appCCloud showingAd]
                 ||
                 [appCCloud showingCutin]);
    
}

/**
 *  データストアに文字列を格納する
 *
 *  @param key   キー
 *  @param value 格納する値
 */
void AppCCloudPlugin::Data::setDataStore(const string& key, const string& value)
{
    NSString *nskey =  cnvStringgToNSString(key);
    NSString *nsvalue = cnvStringgToNSString(value);
    [appCCloud dataStoreSetStringWithKey:nskey string:nsvalue ];
}

/**
 *  データストアに数値を格納する
 *
 *  @param key   キー
 *  @param value 格納する値
 */
void AppCCloudPlugin::Data::setDataStore(const string& key, int value)
{
    NSString *nskey =  cnvStringgToNSString(key);
    [appCCloud dataStoreSetIntegerWithKey:nskey integer:value ];
}

/**
 *  データストアから値を取る
 *
 *  @param key データストアのキー
 *
 *  @return json形式
 */
DataStoreData AppCCloudPlugin::Data::getDataStore(const string& key)
{
    NSString* nsKey = cnvStringgToNSString(key.c_str());

    NSError* err = [[[NSError alloc]init]autorelease];
    long value = [appCCloud dataStoreIntegerWithKey:nsKey ];
    NSDictionary* dicJson = @{@"key": nsKey,
                              @"val": [NSNumber numberWithLong: value],
                              @"text":[appCCloud dataStoreStringWithKey: nsKey ]};
                              //@"text":@""};
    NSData* jsondata = [NSJSONSerialization dataWithJSONObject:dicJson options:0 error: &err];
    NSString *nsJsonstring = [[NSString alloc] initWithData:jsondata encoding:NSUTF8StringEncoding];
    
    string strJson = cnvNSStringToString(nsJsonstring);
    DataStoreData result(strJson);
    return result;
}

/*
   gamers
*/
/**
 *  プレイカウント加算
 */
void AppCCloudPlugin::Gamers::incPlayCount()
{
    [appCCloud gamersPlayCountIncrement];
}

/**
 *  play count取得
 *
 *  @return プレイカウント
 */
int AppCCloudPlugin::Gamers::getPlayCount()
{
    return (int)[appCCloud gamersGetPlayCount];
}

/**
 *  リーダーボードにスコア設定
 *
 *  @param boardId ボードID
 *  @param score   スコア(int)
 */
void AppCCloudPlugin::Gamers::setLeaderBoard(int boardId, int score)
{
    [appCCloud gamersAddLbWithId:boardId scorei:score];
}

/**
 *  リーダーボードにスコア設定
 *
 *  @param boardId ボードID
 *  @param score   スコア(float)
 */
void AppCCloudPlugin::Gamers::setLeaderBoard(int boardId, float score)
{
    [appCCloud gamersAddLbWithId:boardId scored:score];
}

/**
 *  リーダーボードから値を取得
 *
 *  @param boardId ボードID
 *
 *  @return ボードのデータ
 */
LeaderBoardData AppCCloudPlugin::Gamers::getLeaderBoard(int boardId)
{
    NSString* nsJsonStr = [appCCloud gamersGetLbWithId:boardId];
    string strJson = cnvNSStringToString(nsJsonStr);
    LeaderBoardData result(strJson);
    LOGJSON(strJson);
    LOGPARSED(result);
    return result;
}

/**
 *  GAMERS画面への遷移
 */
void AppCCloudPlugin::Gamers::showGamersView()
{
    [appCCloud openGamers];
}

/**
 *  有効なリーダーボード設定
 *
 *  @param leaderBoardIds リーダーボードのID
 */
void AppCCloudPlugin::Gamers::setActiveLeaderBoards(vector<string>& leaderBoardIds)
{
    NSMutableArray* nsIds = [[[NSMutableArray alloc]init]autorelease];
    vector<string>::iterator ldit = leaderBoardIds.begin();
	while( ldit != leaderBoardIds.end() )
	{
        [nsIds addObject:cnvStringgToNSString(*ldit)];
		++ldit;
    }
    [appCCloud gamersSetActiveLbs:nsIds];
}

/**
 *
 *  全データ取得
 *
 *  @return 全データ(json)
 */
vector<PurchaseData> AppCCloudPlugin::Purchase::getAllData()
{
    NSError* err = [[NSError alloc]init];
    NSArray* items = [appCCloud purchaseGetAllData];
    NSMutableArray * outputArray = [[[NSMutableArray alloc]init] autorelease];
    for (NSDictionary *item in items) {
        NSString *category_key = [item objectForKey:@"category_key"];
       
        // make JSON string
        NSString *category_name = [item objectForKey:@"category_name"];
        NSNumber *current_count = [item objectForKey:@"current_count"];
        NSMutableDictionary *ret_item = [NSMutableDictionary dictionary];
        [ret_item setValue:category_key forKey:@"id"];
        [ret_item setValue:category_name forKey:@"name"];
        [ret_item setValue:current_count forKey:@"count"];
        [outputArray addObject:ret_item];
    }
    NSData *data = [NSJSONSerialization dataWithJSONObject:outputArray
                                                   options:NSJSONWritingPrettyPrinted
                                                     error:&err];
    NSString *nsJsonstring = [[NSString alloc] initWithData:data
                                encoding:NSUTF8StringEncoding];
    vector<PurchaseData> result;
    string strJson = cnvNSStringToString(nsJsonstring);
    parseArray<PurchaseData>(strJson, result);
    return result;
}

/**
 * 
 *  アイテム数取得
 *
 *  @param key アイテムkey
 *
 *  @return アイテム数
 */
int AppCCloudPlugin::Purchase::getItemCount(const string& key)
{
    return (int)[appCCloud purchaseGetCountWithKey:cnvStringgToNSString(key)];
}

/**
 *  
 *  アイテム数設定
 *
 *  @param key   アイテムkey
 *  @param count アイテム数
 */
void AppCCloudPlugin::Purchase::setItemCount(const string& key , int count)
{
    [appCCloud purchaseSetCountWithKey:cnvStringgToNSString(key) count:count];
}

/**
 *  アイテム数加算
 *
 *  @param key   アイテムkey
 *  @param count 加算数(アイテム数を減らす場合は負の数を設定)
 */
void AppCCloudPlugin::Purchase::addItemCount(const string& key , int count)
{
    count *= -1;
    [appCCloud purchaseUseCountWithKey:cnvStringgToNSString(key) reduce:count];
}

/**
 *  
 *  アイテム取得
 *
 *  @param key アイテムkey
 *
 *  @return アイテム
 */
PurchaseData  AppCCloudPlugin::Purchase::getItem(const string& key)
{
    string strJson = _purchaseGetJsonItem(key);
    PurchaseData result(strJson);
    return result;
}

/**
 *  アイテムストアの表示
 */
void AppCCloudPlugin::Purchase::openPurchaseView(void)
{
    [appCCloud purchaseShowList];
}

/**
 *  カテゴリー内の有効なアイテムの設定をする
 *
 *  @param key カテゴリーKEY
 *  @param ids アイテムKEY
 */
void AppCCloudPlugin::Purchase::setActiveItems(const string& key, vector<string>& ids)
{
    
    NSMutableArray* array = [[NSMutableArray alloc] init];
    
    vector<string>::iterator it = ids.begin();
    while( it != ids.end() )
	{
        [array addObject:cnvStringgToNSString(*it)];
        ++it;
    }
    [appCCloud purchaseAddActiveKey:cnvStringgToNSString(key) ids:array];
}

/**
 *  アプリ内サービス呼び出し（ポイント）
 */
void  AppCCloudPlugin::Reward::openRewardPointView()
{
    [appCCloud rewardShowListPoint];
}

/**
 *  アプリ内サービス呼び出し
 *
 *  @param serviceId サービスID
 */
void AppCCloudPlugin::Reward::openRewardServiceViews(const string& serviceId)
{
    [appCCloud rewardShowListServiceWithId:cnvStringgToNSString(serviceId)];
}

/**
 *  リワードサービスか否か
 *
 *  @param service_id サービスID
 *
 *  @return true: サービス false サービスではない
 */
bool AppCCloudPlugin::Reward::isRewardService(const string& service_id)
{
    return (0 != [arrServiceId containsObject:
                 [NSString stringWithUTF8String:service_id.c_str()]]);
}

/**
 *  リワードサービスクリア
 *
 *  @param service_id サービスID
 */
void AppCCloudPlugin::Reward::rewardClearService(const string& service_id)
{
    [arrServiceId removeObject:[NSString stringWithUTF8String:service_id.c_str()]];
}

/**
 * サービス追加
 */
void AppCCloudPlugin::Reward::getService(const string& service_id)
{
    [arrServiceId addObject: cnvStringgToNSString(service_id)];
}

/**
 *  appCHorizontalへ変換
 *
 *  @param AppCCloudPlugin::Horizontal
 *  @return appCHorizontal
 */
static appCHorizontal cnvAppCHorizontal(AppCCloudPlugin::Horizontal horizontal)
{
    switch (horizontal) {
        case AppCCloudPlugin::LEFT:
            return appCHorizontalLeft;
        case AppCCloudPlugin::CENTER:
            return appCHorizontalCenter;
        case AppCCloudPlugin::RIGHT:
            return appCHorizontalRight;
        default:
            return appCHorizontalCenter;
    }
}

/**
 *  appCVerticalへ変換
 *
 *  @param AppCCloudPlugin::Vertical
 *  @return AppCVertical
 */
static appCVertical cnvAppCVertical(AppCCloudPlugin::Vertical vertical)
{
    switch (vertical) {
        case AppCCloudPlugin::TOP:
            return appCVerticalTop;
        case AppCCloudPlugin::BOTTOM:
            return appCVerticalBottom;
        default:
            return appCVerticalBottom;
    }
}

/**
 *  std::string -> NSString
 *
 *  @param key std::string
 *
 *  @return NSString
 */
NSString* cnvStringgToNSString(const string& key){
    NSString *nskey =  [NSString stringWithCString: key.c_str()  encoding: NSUTF8StringEncoding];
    return nskey;
}

/**
 *  NSString -> std::string
 *
 *  @param key NSString
 *
 *  @return std::string
 */
string cnvNSStringToString(NSString* nsString){
    return string((char *) [nsString UTF8String]);
}

/**
 *  RootView取得
 *
 *  @return UIView
 */
static UIView* getRootView()
{
    UIView *rootView = [UIApplication sharedApplication].keyWindow.rootViewController.view;
    return rootView;
}

/**
 *  ViewController取得
 *
 *  @return UIViewController
 */
static UIViewController* getViewController()
{
    UIViewController *viewController = [UIApplication sharedApplication].keyWindow.rootViewController;
    return viewController;
}

/**
 *  指定したカテゴリーのアイテム値を返す。
 *
 *  @param key カテゴリーのキー
 *
 *  @return json形式
 */
static string _purchaseGetJsonItem(const string& key)
{
    NSString *ret = @"";
    NSString *key0 = cnvStringgToNSString(key);
    NSArray *items = [appCCloud purchaseGetAllData];
    for (NSDictionary *item in items) {
        NSString *category_key = [item objectForKey:@"category_key"];
        if ([key0 isEqualToString:category_key]) {
            // make JSON string
            NSString *category_name = [item objectForKey:@"category_name"];
            NSNumber *current_count = [item objectForKey:@"current_count"];
            NSMutableDictionary *ret_item = [NSMutableDictionary dictionary];
            [ret_item setValue:category_key forKey:@"id"];
            [ret_item setValue:category_name forKey:@"name"];
            [ret_item setValue:current_count forKey:@"count"];
            NSData *data = [NSJSONSerialization dataWithJSONObject:ret_item
                                                           options:NSJSONWritingPrettyPrinted
                                                             error:nil];
            ret = [[NSString alloc] initWithData:data
                                        encoding:NSUTF8StringEncoding];
            break;
        }
    }
    return cnvNSStringToString(ret);
}



/**
 *  コンストラクタ
 */
PurchaseData::PurchaseData(const string& strJson)
{
    Json* jsonObj = Json_create(strJson.c_str());
    if(!jsonObj){
        return ;
    }
    LOGJSON(strJson);
    LOGPARSED(*this);
    Json_dispose(jsonObj);
}

/**
 *  コンストラクタ
 */
PurchaseData::PurchaseData(Json* jsonObject)
{
    setMembers(jsonObject);
}

/**
 *  コンストラクタ
 */
PurchaseData::PurchaseData(const PurchaseData& src):_id(src._id),_name(src._name),_count(src._count)
{
}
/**
 *  Jsonからメンバに値を入れる。
 *
 *  @param jsonObject Jsonオブジェクト
 */
void PurchaseData::setMembers(Json* jsonObject){
    setId( Json_getString(jsonObject, "id", "") );
    setName( Json_getString(jsonObject, "name" , "") );
    setCount( Json_getInt(jsonObject, "count", -1) );
}
/**
 *  ID取得
 *
 *  @return ID
 */
string PurchaseData::getId() const
{
    return _id;
}

/**
 *  id設定
 *
 *  @param id id
 */
void PurchaseData::setId(const string& id){
    _id = id;
}

/**
 *  名前設定
 *
 *  @return 名前
 */
string PurchaseData::getName() const
{
    return _name;
}

/**
 *  名前設定
 *
 *  @param name 名前
 */
void PurchaseData::setName(const string& name){
    _name = name;
}

/**
 *  アイテム数取得
 *
 *  @return アイテム数
 */
int PurchaseData::getCount() const
{
    return _count;
}

/**
 *  アイテム数設定
 *
 *  @param count アイテム数
 */
void PurchaseData::setCount(int count)
{
    _count = count;
}

/**
 *  コンストラクタ
 */
LeaderBoardData::LeaderBoardData(const string& strJson){
    Json* jsonObject = Json_create(strJson.c_str());
    if(!jsonObject)
    {
        return ;
    }
    setMembers(jsonObject);
    LOGJSON(strJson);
    LOGPARSED(*this);
    Json_dispose(jsonObject);
}

/**
 *  コンストラクタ
 */
LeaderBoardData::LeaderBoardData(Json* jsonObject){
    setMembers(jsonObject);
}

/**
 *  コンストラクタ
 */
LeaderBoardData::LeaderBoardData(const LeaderBoardData& src):_id(src._id),_name(src._name),_score(src._score),_time(src._time)
{
}

/**
 *  Jsonからメンバに値を入れる。
 *
 *  @param jsonObject Jsonオブジェクト
 */
void LeaderBoardData::setMembers(Json* jsonObject){
    setId( Json_getString(jsonObject, "id", "") );
    setName( Json_getString(jsonObject, "name" , "") );
    setScore( Json_getInt(jsonObject, "score", -1) );
    setTime( Json_getFloat(jsonObject, "time", -99999.99) );
}

/**
 *  Id取得
 *
 *  @return Id
 */
string LeaderBoardData::getId() const
{
    return _id;
}

/**
 *  Id設定
 *
 *  @param id Id
 */
void LeaderBoardData::setId(const string& id)
{
    _id = id;
}

/**
 *  名前取得
 *
 *  @return 名前
 */
string LeaderBoardData::getName() const
{
    return _name;
}

/**
 *  名前設定
 *
 *  @param name 名前
 */
void LeaderBoardData::setName(const string& name)
{
    _name = name;
}

/**
 *  点数取得
 *
 *  @return 点数
 */
int LeaderBoardData::getScore() const
{
    return _score;
}

/**
 *  点数設定
 *
 *  @param score 点数
 */
void LeaderBoardData::setScore(int score)
{
    _score = score;
}

/**
 *  時刻取得
 *
 *  @return 時刻
 */
float LeaderBoardData::getTime() const
{
    return _time;
}

/**
 *  時刻設定
 *
 *  @param time 時刻
 */
void LeaderBoardData::setTime(float time)
{
    _time = time;
}

/**
 *  コンストラクタ
 */
DataStoreData::DataStoreData(const string& strJson){
    Json* jsonObject = Json_create(strJson.c_str());
    if(!jsonObject)
    {
        return ;
    }
    setMembers(jsonObject);
    LOGJSON(strJson);
    LOGPARSED(*this);
    Json_dispose(jsonObject);
}

/**
 *  コンストラクタ
 */
DataStoreData::DataStoreData(Json* jsonObject){
    setMembers(jsonObject);
}

/**
 *  コンストラクタ
 *
 *  @param src　コピー元
 */
DataStoreData::DataStoreData(const DataStoreData& src):_key(src._key), _text(src._text), _val(src._val)
{
}

/**
 *  jsonからメンバへコピーする
 *
 *  @param jsonObject Jsonオブジェクト
 */
void DataStoreData::setMembers(Json* jsonObject){
    setKey(Json_getString(jsonObject, "key", "") );
    setText(Json_getString(jsonObject, "text", "") );
    setVal(Json_getInt(jsonObject, "val", -1));
}

/**
 *  id取得
 *
 *  @return id
 */
string DataStoreData::getKey() const
{
    return _key;
}

/**
 *  id取得
 *
 *  @param id id
 */
void DataStoreData::setKey(const string& key)
{
    _key = key;
}

/**
 *  文字列取得
 *
 *  @return 文字列
 */
string DataStoreData::getText() const
{
    return _text;
}

/**
 *  文字列設定
 *
 *  @param text 文字列
 */
void DataStoreData::setText(const string& text)
{
    _text = text;
}

/**
 *  数値データ取得
 *
 *  @return 数値データ
 */
int DataStoreData::getVal() const
{
    return _val;
}

/**
 *  数値データ設定
 *
 *  @param val 数値データ
 */
void DataStoreData::setVal(int val)
{
    _val = val;
}


#endif
