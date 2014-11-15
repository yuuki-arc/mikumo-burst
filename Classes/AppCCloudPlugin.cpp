//
// AppCCloudPlugin.cpp
//
// appC cloud Plugin Cocos2d-x
// Created by cayto inc.
//

#include "AppCCloudPlugin.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

//AndroidPlugin Java Class
#define CLASS_NAME "net/app_c/cloud/plugin/c2dx/AppCCloudPlugin"
using namespace std;

jclass _getClassID(const char *className);
bool AppCCloudPlugin::appCCloudStartedFlag = false;

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
AppCCloudPlugin& AppCCloudPlugin::setMK_iOS(const string& mk )
{
    return getInstance();
}
/**
 *  option設定
 *
 *  @param options オプション
 */
AppCCloudPlugin& AppCCloudPlugin::setOptions(int options)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "setOptions", "(I)V"))
    {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, options);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    return getInstance();
}

/**
 *  appCCloundPlugin 終了処理
 */
void AppCCloudPlugin::finish()
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "finish", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  appCCloundPlugin開始
 */
bool AppCCloudPlugin::start()
{
    jboolean jReturnValue = false;
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "start", "()Z"))
    {
        jReturnValue = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    return jReturnValue;
}

/**
 *  リリースステータス取得
 *
 *  @return リリース状態
 */
int AppCCloudPlugin::getReleaseStatus()
{
    return AppCCloudPlugin::ReleaseStatusReadyForSale;
}

/**
 *  広告リスト型表示
 */
void AppCCloudPlugin::Ad::openAdListView()
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "callAdListActivity", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  シンプル型表示
 *
 *  @param vertical  表示縦位置
 *  @param skinColor スキンカラー
 *  @param textColor テキストカラー
 */
void AppCCloudPlugin::Ad::showSimpleView(Vertical vertical, const string& skinColor, const string& textColor)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showSimpleView", "(ILjava/lang/String;Ljava/lang/String;)V")) {
        jstring strSkinColor = methodInfo.env->NewStringUTF(skinColor.c_str());
        jstring strTextColor = methodInfo.env->NewStringUTF(textColor.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, vertical, strSkinColor, strTextColor);
        methodInfo.env->DeleteLocalRef(strSkinColor);
        methodInfo.env->DeleteLocalRef(strTextColor);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  シンプル型非表示
 */
void AppCCloudPlugin::Ad::hideSimpleView()
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "hideSimpleView", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  ムーヴアイコン型表示
 *
 *  @param horizontal 表示横位置
 *  @param vertical   表示縦位置
 *  @param skinColor  スキンカラー
 *  @param textColor  テキストカラー
 */
void AppCCloudPlugin::Ad::showMoveIconView(Horizontal horizontal, Vertical vertical, const string& skinColor, const string& textColor)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showMoveIconView", "(IILjava/lang/String;Ljava/lang/String;)V")) {
        jstring strSkinColor = methodInfo.env->NewStringUTF(skinColor.c_str());
        jstring strTextColor = methodInfo.env->NewStringUTF(textColor.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, horizontal, vertical, strSkinColor, strTextColor);
        methodInfo.env->DeleteLocalRef(strSkinColor);
        methodInfo.env->DeleteLocalRef(strTextColor);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  ムーヴアイコン型非表示
 */
void AppCCloudPlugin::Ad::hideMoveIconView()
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "hideMoveIconView", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
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
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showMarqueeView", "(ILjava/lang/String;)V")) {
        jstring strTextColor = methodInfo.env->NewStringUTF(textColor.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, vertical, strTextColor);
        methodInfo.env->DeleteLocalRef(strTextColor);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  マーキー型非表示
 */
void AppCCloudPlugin::Ad::hideMarqueeView()
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "hideMarqueeView", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  カットイン型表示
 */
void AppCCloudPlugin::Ad::showCutin()
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "callCutin", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}
/**
 *  カットイン型表示（アプリケーション終了ボタン付き）
 *　Androidのみ有効
 */
void AppCCloudPlugin::Ad::showCutinFinish()
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "callCutinFinish", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  マッチアップ表示(バナー)
 *
 *  @param horizontal 表示横位置
 *  @param vertical 表示縦位置
 */
void AppCCloudPlugin::Ad::showMatchAppView(Horizontal horizontal, Vertical vertical)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showMatchAppBannerView", "(II)V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, horizontal, vertical);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  マッチアップ非表示(バナー)
 */
void AppCCloudPlugin::Ad::hideMatchAppView() {
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "hideMatchAppBannerView", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  リコネクトバナー表示
 */
void AppCCloudPlugin::Ad::showRecBannerView(Vertical vertical)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showRecBannerView", "(I)V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, vertical);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  リコネクトバナー非表示
 */
void AppCCloudPlugin::Ad::hideRecBannerView()
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "hideRecBannerView", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  リコネクトインタースティシャル表示
 */
void AppCCloudPlugin::Ad::showRecInterstitial()
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "callRecInterstitial", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  リコネクトインタースティシャル(終了)表示
 */
void AppCCloudPlugin::Ad::showRecInterstitialFinish()
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "callRecInterstitialFinish", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  全広告非表示
 */
void AppCCloudPlugin::Ad::hideAllAdViews()
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "hideAllAdViews", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}
/**
 *  広告前面確認.
 *
 *  @return true:前面　false:後面
 */
bool AppCCloudPlugin::Ad::isForegroundAd()
{
    jboolean jReturnValue = false;
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "IsForegroundAd", "()Z"))
    {
        jReturnValue = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    return jReturnValue;
    
}


/**
 *  データストアに文字列を格納する
 *
 *  @param key   キー
 *  @param value 格納する値
 */
void AppCCloudPlugin::Data::setDataStore(const string& key, const string& value)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "setDataStore", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring strKey = methodInfo.env->NewStringUTF(key.c_str());
        jstring strValue = methodInfo.env->NewStringUTF(value.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, strKey, strValue);
        methodInfo.env->DeleteLocalRef(strKey);
        methodInfo.env->DeleteLocalRef(strValue);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  データストアに数値を格納する
 *
 *  @param key   キー
 *  @param value 格納する値
 */
void AppCCloudPlugin::Data::setDataStore(const string& key, int value)
{
    JniMethodInfo methodInfo;
     if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "setDataStore", "(Ljava/lang/String;I)V")) {
        jstring strKey = methodInfo.env->NewStringUTF(key.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, strKey, value);
        methodInfo.env->DeleteLocalRef(strKey);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *
 *  @param key データストアのkey
 *
 *  @return DataStoreValueインスタンス
 */
DataStoreData AppCCloudPlugin::Data::getDataStore(const string &key)
{
    string strJson="";
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "getDataStore", "(Ljava/lang/String;)Ljava/lang/String;")) {
        jstring strKey = methodInfo.env->NewStringUTF(key.c_str());
        jobject objResult = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, strKey);
        // jstringをstd::stringに変換
        strJson = JniHelper::jstring2string((jstring)objResult);
        methodInfo.env->DeleteLocalRef(strKey);
        methodInfo.env->DeleteLocalRef(objResult);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);

    }
    DataStoreData result(strJson);

    return result;
}

/**
 *  アイテムストアの表示
 */
void AppCCloudPlugin::Purchase::openPurchaseView(void)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "openPurchaseView", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  プレイカウント加算
 */
void AppCCloudPlugin::Gamers::incPlayCount()
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "incPlayCount", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  play count取得
 *
 *  @return プレイカウント
 */
int AppCCloudPlugin::Gamers::getPlayCount()
{
    int ret = -1;
    
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "getPlayCount", "()I")) {
        ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    return ret;
}

/**
 *  リーダーボードにスコア設定
 *
 *  @param id    リーダーボードのID
 *  @param score スコア
 */
void AppCCloudPlugin::Gamers::setLeaderBoard(int id, int score)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "setLeaderBoard", "(II)V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, id, score
                                             );
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}
/**
 *  リーダーボードにスコア設定
 *
 *  @param id    リーダーボードのID
 *  @param score スコア
 */
void AppCCloudPlugin::Gamers::setLeaderBoard(int id, float score)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "setLeaderBoard", "(IF)V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, id, score
                                             );
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
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
    JniMethodInfo methodInfo;
    string strJson;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "getLeaderBoard", "(I)Ljava/lang/String;")) {
        
        jobject objResult = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID,boardId);
        // jstringをstd::stringに変換
        strJson = JniHelper::jstring2string((jstring)objResult);
        // 後処理
        methodInfo.env->DeleteLocalRef(objResult);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
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
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showGamersView", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  有効なリーダーボードの設定
 *
 *  @param ids リーダーボードID
 */
void AppCCloudPlugin::Gamers::setActiveLeaderBoards(vector<string>& ids)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "setActiveLeaderBoards", "([Ljava/lang/String;)V")) {
        
        int iLength = ids.size();
        jclass classIDtmp = methodInfo.env->FindClass("java/lang/String");
        jobjectArray joArray = methodInfo.env->NewObjectArray(iLength,
                                                              classIDtmp,
                                                              methodInfo.env->NewStringUTF(""));
        for(int i=0; i<iLength; i++) {
            jstring strIds = methodInfo.env->NewStringUTF(ids[i].c_str());
            methodInfo.env->SetObjectArrayElement(joArray, i, strIds);
        }
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, joArray);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(joArray);
    }
}

// purchase

/**
 *  全アイテム取得
 *
 *  @return json
 */
vector<PurchaseData> AppCCloudPlugin::Purchase::getAllData()
{
    string strJson="";
    vector<PurchaseData> result;
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "getItems", "()Ljava/lang/String;")) {
        jobject objResult = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
  
        // jstringをstd::stringに変換
        strJson = JniHelper::jstring2string((jstring)objResult);
        
        methodInfo.env->DeleteLocalRef(objResult);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        parseArray<PurchaseData>(strJson, result);
    }
    return result;
}

/**
 *  アイテム数取得
 *
 *  @param key アイテムkey
 *
 *  @return アイテム数
 */
int AppCCloudPlugin::Purchase::getItemCount(const string& key)
{
    int ret = -1;
    
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "getItemCount", "(Ljava/lang/String;)I")) {
        jstring strKey = methodInfo.env->NewStringUTF(key.c_str());
        ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID, strKey);
        
        methodInfo.env->DeleteLocalRef(strKey);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    return ret;
}

/**
 *  アイテム数設定
 *
 *  @param key   アイテムkey
 *  @param count アイテム数
 */
void AppCCloudPlugin::Purchase::setItemCount(const string& key, int count)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "setItemCount", "(Ljava/lang/String;I)V")) {
        jstring strKey = methodInfo.env->NewStringUTF(key.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, strKey, count);
        methodInfo.env->DeleteLocalRef(strKey);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  アイテム数加算
 *
 *  @param string& アイテムkey
 *  @param count   加算数(アイテム数を減らす場合は負の数を設定)
 */
void AppCCloudPlugin::Purchase::addItemCount(const string& key, int count)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "addItemCount", "(Ljava/lang/String;I)V")) {
        jstring strKey = methodInfo.env->NewStringUTF(key.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, strKey, count);
        methodInfo.env->DeleteLocalRef(strKey);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  アイテム取得
 *
 *  @param string& アイテムキー
 *
 *  @return アイテム(JSON)
 */
PurchaseData AppCCloudPlugin::Purchase::getItem(const string& key)
{
    
    std::string strJson="";
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "getItem", "(Ljava/lang/String;)Ljava/lang/String;")) {
        jstring strKey = methodInfo.env->NewStringUTF(key.c_str());
        
        jobject objResult = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, strKey);
        
        // jstringをstd::stringに変換
        strJson = JniHelper::jstring2string((jstring)objResult);
        
        methodInfo.env->DeleteLocalRef(strKey);
        methodInfo.env->DeleteLocalRef(objResult);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        
    }
    PurchaseData result(strJson);
    return result;
}

/**
 *  カテゴリー内の有効なアイテムの設定をする
 *
 *  @param key カテゴリーKEY
 *  @param ids アイテムKEY
 */
void AppCCloudPlugin::Purchase::setActiveItems(const string& key, vector<string>& ids)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "setActiveItems", "(Ljava/lang/String;[Ljava/lang/String;)V")) {
        
        jstring strKey = methodInfo.env->NewStringUTF(key.c_str());
        
        int iLength = ids.size();
        jclass classIDtmp = methodInfo.env->FindClass("java/lang/String");
        jobjectArray joArray = methodInfo.env->NewObjectArray(iLength,
                                                              classIDtmp,
                                                              methodInfo.env->NewStringUTF(""));
        for(int i=0; i<iLength; i++) {
            jstring strIds = methodInfo.env->NewStringUTF(ids[i].c_str());
            methodInfo.env->SetObjectArrayElement(joArray, i, strIds);
        }
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, strKey, joArray);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(joArray);
        methodInfo.env->DeleteLocalRef(strKey);
    }
}


/**
 *  ポイントビューを開く
 */
void AppCCloudPlugin::Reward::openRewardPointView()
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showRewardPointView", "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

/**
 *  アプリ内サービス呼び出し
 *
 *  @param serviceId サービスID
 */
void AppCCloudPlugin::Reward::openRewardServiceViews(const string& key)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "showRewardServiceView", "(Ljava/lang/String;)V")) {
        jstring strKey = methodInfo.env->NewStringUTF(key.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, strKey);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(strKey);
    }
}

/**
 *  リワードサービスか否か
 *
 *  @param service_id サービスID
 *
 *  @return true: サービス false サービスではない
 */
bool AppCCloudPlugin::Reward::isRewardService(const string& serviceId)
{
    jboolean jReturnValue = false;;
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "isRewardService", "(Ljava/lang/String;)Z")) {
        jstring strKey = methodInfo.env->NewStringUTF(serviceId.c_str());
        jReturnValue = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, strKey);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(strKey);
    }
    return jReturnValue;
}

/**
 *  リワードサービスクリア
 *
 *  @param service_id サービスID
 */
void AppCCloudPlugin::Reward::rewardClearService(const string& serviceId)
{
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "clearRewardService", "(Ljava/lang/String;)V")) {
        jstring strServiceId = methodInfo.env->NewStringUTF(serviceId.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, strServiceId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(strServiceId);
    }
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
 *  DataStoreデータ格納クラス
 */

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
    setKey(Json_getString(jsonObject, "key", ""));
    setText(Json_getString(jsonObject, "text", ""));
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

