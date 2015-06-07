#include "scene/LoadingScene.h"
#include "scene/TitleSceneLoader.h"
#include "scene/SelectSceneLoader.h"
//#include "scene/StorySceneLoader.h"
#include "scene/SelectStorySceneLoader.h"
#include "tools/GoogleAnalyticsTracker.h"
#include "resources/AppsInformation.h"
#include "resources/DownloadCacheManager.h"
#include "factory/TextCreator.h"
#include <unistd.h>

LoadingScene::LoadingScene()
: appsInfoCacheStatus(AppsInfoCacheStatus::NoCache)
{
}

LoadingScene::~LoadingScene()
{
}

bool LoadingScene::init()
{    
    CCLOG("LoadingScene::init");
//    GoogleAnalyticsTracker::sendScreen("LoadingScene");
	if(!Layer::init())
	{
		return false;
	}
    
	return true;
}

void LoadingScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // メッセージ表示
    float labelWidth = origin.x + visibleSize.width * 1 / 10;
    float relativeLabelHeight;
    Label* resultLabel;
    Point point;

    relativeLabelHeight = 6.5f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("ロード中…", point);
    resultLabel->setScale(BM_FONT_SIZE64(20));
    this->addChild(resultLabel);
    
    // アプリ情報をネットワークからダウンロード
    downloadAppsUpdate();
    
    // スケジュール更新
    this->scheduleUpdate();
}

/**
 *  アプリ更新情報をダウンロードする
 *  ※ローカルにアプリ情報のキャッシュを保持していない場合は、
 *   ダウンロードデータをキャッシュへ書き込むところまで行う
 */
void LoadingScene::downloadAppsUpdate()
{
    appsInfo = AppsInformation::create();
    appsInfo->retain();
    if (appsInfo->isExistCacheFile())
    {
        // キャッシュが存在する場合はデータダウンロードのみ行う
        setAppsInfoCacheStatus(AppsInfoCacheStatus::ExistCache);
        appsInfo->downloadData();
    }
    else
    {
        // キャッシュが存在しない場合はデータダウンロードに加えてキャッシュ書き込みを行う
        setAppsInfoCacheStatus(AppsInfoCacheStatus::NoCache);
        appsInfo->downloadAndWriteCacheData();
    }
    
    this->loadingFlg = true;
}

/**
 *  定期更新（フレーム毎）
 *
 *  @param frame フレーム
 */
void LoadingScene::update(float frame)
{
    // アプリ情報キャッシュの状態によりコールバック関数を切り替える（終了チェックの判定が異なるため）
    bool result = false;
    switch (getAppsInfoCacheStatus()) {
        case AppsInfoCacheStatus::ExistCache:
            result = appsInfo->downloadCache->execCallback();
            break;
        case AppsInfoCacheStatus::NoCache:
            result = appsInfo->downloadCache->execCallbackReferenceData();
            break;
        default:
            CCLOG("LoadingScene::cache status error");
            break;
    }
    if (!result)
    {
        CCLOG("LoadingScene::read error");
    }
    
    // ローディングが終了したら終了後処理を実行
    if (this->loadingFlg &&
        appsInfo->downloadCache->loadStatus == DownloadCacheManager::LoadStatus::LoadComplete)
    {
        // アプリの最新バージョンチェック
        bool check = checkAppsUpdate();

        if (check) {
            // 最新バージョンがなければゲーム画面に遷移する
            replaceSelectScene();
        }
        else
        {
            // 何らかのチェックに引っかかった場合はタイトル画面に戻る
            replaceTitleScene();
        }
    }
}

/**
 *  アプリの最新状態をチェックする
 */
bool LoadingScene::checkAppsUpdate()
{
    // ローカル内のファイルと比較して更新チェック
    DownloadCacheManager* localFile = DownloadCacheManager::create();
    localFile->retain();
    localFile->setFileName(Constant::CACHE_FILE_APPS());
    localFile->readCache();
    
    // ローカルファイルのアプリ情報を取得
    picojson::object& sheets = localFile->loader->jsonResult.get<picojson::object>();
    picojson::array& sheetColumns = sheets[Constant::SHEET_NAME_AP_APPS()].get<picojson::array>();
    std::string localUpdateVersionDate = "";
    std::string localUpdateSheetDate = "";
    for (picojson::array::iterator it = sheetColumns.begin(); it != sheetColumns.end(); it++)
    {
        picojson::object& column = it->get<picojson::object>();
        std::string device = (std::string)column["device"].get<std::string>();
        if (device == Constant::SHEET_COLUMN_AP_APPS())
        {
            localUpdateVersionDate = (std::string)column["updateVersionDate"].get<std::string>();
            localUpdateSheetDate = (std::string)column["updateSheetDate"].get<std::string>();
        }
    }
    
    // シナリオデータの最新バージョンが存在する場合はキャッシュデータを削除
    if (appsInfo->getUpdateSheetDate() != localUpdateSheetDate)
    {
        // キャッシュデータ削除
        DownloadCacheManager::removeCacheData(Constant::CACHE_FILE_STORY());
        // 最新データをキャッシュ書き込み
        appsInfo->writeCache();
        
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();
        
        // メッセージ表示
        float labelWidth = origin.x + visibleSize.width * 1 / 10;
        float relativeLabelHeight;
        Label* resultLabel;
        Point point;
        
        relativeLabelHeight = 5.5f;
        point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
        resultLabel = TextCreator::create("シナリオキャッシュをクリア", point);
        resultLabel->setScale(BM_FONT_SIZE64(20));
        this->addChild(resultLabel);
    }
    
    return true;
}

/**
 *  画面遷移処理（タイトル画面）
 */
void LoadingScene::replaceTitleScene()
{
    Scene* scene = TitleSceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}

/**
 *  画面遷移処理（キャラクターセレクト画面）
 */
void LoadingScene::replaceSelectScene()
{
    // テクスチャアトラスを読み込む
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("character/enemy2/enemy2.plist");
    frameCache->addSpriteFramesWithFile("character/persona2/persona2.plist");
    frameCache->addSpriteFramesWithFile("misc/misc.plist");
    frameCache->addSpriteFramesWithFile("effect/battleEffectB0.plist");
    
//    Scene* scene = SelectSceneLoader::createScene();
//    Scene* scene = StorySceneLoader::createScene();
    Scene* scene = SelectStorySceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}

