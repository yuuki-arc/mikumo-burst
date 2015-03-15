#include "scene/LoadingScene.h"
//#include "scene/SelectSceneLoader.h"
#include "scene/StorySceneLoader.h"
#include "core/GameManager.h"
#include "tools/GoogleAnalyticsTracker.h"
#include "resources/SoundManager.h"
#include "resources/AppsInformation.h"
#include "resources/DownloadCacheManager.h"
#include "factory/TextCreator.h"

LoadingScene::LoadingScene()
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
    
    // アプリ情報を取得
    checkAppsUpdate();
    
    // スケジュール更新
    this->scheduleUpdate();
}

/**
 *  アプリ更新情報チェック
 */
void LoadingScene::checkAppsUpdate()
{
    appsInfo = AppsInformation::create(DownloadCacheMode::CacheMemory);
    appsInfo->retain();
    if (appsInfo->isExistCacheFile())
    {
        // キャッシュが存在する場合はデータダウンロードのみ行う
        appsInfo->downloadData();
    }
    else
    {
        // キャッシュが存在しない場合はデータダウンロードに加えてキャッシュ書き込みを行う
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
    // アプリ情報の非同期読み込み処理
    bool result = appsInfo->downloadCache->execCallback();
//    bool result = appsInfo->downloadCache->execCallbackReferenceData();
    if (!result)
    {
        CCLOG("LoadingScene::read error");
    }
    
    // ローディングが終了したら終了後処理を実行
    if (this->loadingFlg)
    {
        CCLOG("loadingFlg true");
        if (appsInfo->downloadCache->loadStatus == DownloadCacheManager::LoadStatus::LoadComplete)
        {
            // ローカル内のファイルと比較して更新チェック
            DownloadCacheManager* localFile = DownloadCacheManager::create();
            localFile->retain();
            localFile->setFileName(Constant::CACHE_FILE_APPS());
            localFile->readCache();
//            localFile->loadData();
            
            // ローカルファイルのアプリ情報を取得
            picojson::object& sheets = localFile->loader->jsonResult.get<picojson::object>();
            CCLOG("download-cache true");
            picojson::array& sheetColumns = sheets[Constant::SHEET_NAME_AP_APPS()].get<picojson::array>();
            std::string localUpdateVersionDate = "";
            std::string localUpdateSheetDate = "";
            for (picojson::array::iterator it = sheetColumns.begin(); it != sheetColumns.end(); it++)
            {
                CCLOG("test");
                picojson::object& column = it->get<picojson::object>();
                std::string device = (std::string)column["device"].get<std::string>();
                if (device == Constant::SHEET_COLUMN_AP_APPS())
                {
                    localUpdateVersionDate = (std::string)column["updateVersionDate"].get<std::string>();
                    localUpdateSheetDate = (std::string)column["updateSheetDate"].get<std::string>();
                }
            }
            // 画面遷移
            endLoading();
        }
    }
}

/**
 *  ローディング終了後処理
 */
void LoadingScene::endLoading()
{
    // テクスチャアトラスを読み込む
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("character/enemy2/enemy2.plist");
    frameCache->addSpriteFramesWithFile("character/persona2/persona2.plist");
    frameCache->addSpriteFramesWithFile("misc/misc.plist");
    frameCache->addSpriteFramesWithFile("effect/battleEffectB0.plist");
    
    //    Scene* scene = SelectSceneLoader::createScene();
    Scene* scene = StorySceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}

