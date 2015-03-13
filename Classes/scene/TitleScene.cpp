#include "scene/TitleScene.h"
//#include "scene/SelectSceneLoader.h"
#include "scene/StorySceneLoader.h"
#include "core/GameManager.h"
#include "tools/GoogleAnalyticsTracker.h"
#include "resources/SoundManager.h"
#include "resources/AppsInformation.h"
#include "resources/DownloadCacheManager.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

bool TitleScene::init()
{    
    CCLOG("TitleScene::init");
//    GoogleAnalyticsTracker::sendScreen("TitleScene");
	if(!Layer::init())
	{
		return false;
	}
    
	return true;
}

SEL_MenuHandler TitleScene::onResolveCCBCCMenuItemSelector(Ref *pTarget, const char *pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    return NULL;
}

Control::Handler TitleScene::onResolveCCBCCControlSelector(Ref *pTarget, const char *pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedStartButton", TitleScene::tappedStartButton);
    return NULL;
}

void TitleScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    CCLOG("TitleScene::onNodeLoaded");
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    Size screenSize = director->getWinSize();

    // アプリ情報を取得
    checkAppsUpdate();
    
    // BGM
    SoundManager* soundManager = new SoundManager();
    soundManager->playBGM("bgm_title");
    
    // SE
    soundManager->preloadSE("se_select");
    
    // エフェクト
    ParticleSystemQuad* particle1 = ParticleSystemQuad::create("particle/title_particle1.plist");
    particle1->setPosition(Vec2(screenSize.width * 14 / 40, screenSize.height * 13 / 40));
    this->addChild(particle1);
    ParticleSystemQuad* particle2 = ParticleSystemQuad::create("particle/title_particle2.plist");
    particle2->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(particle2);
    
    // スケジュール更新
    this->scheduleUpdate();
}

/**
 *  定期更新（フレーム毎）
 *
 *  @param frame フレーム
 */
void TitleScene::update(float frame)
{
    // アプリ情報の非同期読み込み処理
    bool result = appsInfo->downloadCache->execCallback();
    if (!result)
    {
        CCLOG("TitleScene::read error");
    }
    
    // ローディングが終了したら終了後処理を実行
    if (this->loadingFlg)
    {
        if (appsInfo->downloadCache->loadStatus == DownloadCacheManager::LoadStatus::LoadComplete)
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
 *  Startボタンタップ時処理
 *
 *  @param pTarget           pTarget
 *  @param pControlEventType pControlEventType
 */
void TitleScene::tappedStartButton(Ref *pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedStartButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    
    this->loadingFlg = true;
}

/**
 *  アプリ更新情報チェック
 */
void TitleScene::checkAppsUpdate()
{
    appsInfo = AppsInformation::create(DownloadCacheMode::CacheMemory);
    appsInfo->retain();
    appsInfo->downloadData();
}

/**
 *  ローディング終了後処理
 */
void TitleScene::endLoading()
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

