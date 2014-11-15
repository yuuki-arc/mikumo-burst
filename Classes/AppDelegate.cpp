#include "AppDelegate.h"
#include "extensions/cocos-ext.h"

#include "AppCCloudPlugin.h"
#include "Constant.h"
#include "GameManager.h"
#include "TitleScene.h"
#include "TitleSceneLoader.h"
#include "SimpleAudioEngine.h"
#include "UserDataStore.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    
    srand((unsigned int)time(NULL));
    
    Size designSize = Size(320, 480); // ベースサイズ
    Size resourceSize;
    Size screenSize = glview->getFrameSize();   //画面サイズ取得
    
    std::vector<std::string> searchPaths;
    std::vector<std::string> resDirOrders;

    searchPaths.push_back("Resources");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
    CCLOG("height: %f, width: %f", screenSize.width, screenSize.height);

    if (screenSize.height >= 960) {
        resourceSize = Size(640, 960);
        resDirOrders.push_back("resources-iphonehd");
        GameManager::getInstance()->screenMode = ScreenModeHd;
    } else {
        resourceSize = Size(320, 480);
        resDirOrders.push_back("resources-iphone");
        GameManager::getInstance()->screenMode = ScreenModeSd;
    }
    
    resDirOrders.push_back("font");
    FileUtils::getInstance()->setSearchPaths(resDirOrders);
    
    const float scaleW = resourceSize.width / designSize.width;
    const float scaleH = resourceSize.height / designSize.height;
    
    // 縦(Portrait)の場合
    const ResolutionPolicy policy = scaleW > scaleH ?
        ResolutionPolicy::FIXED_HEIGHT :
        ResolutionPolicy::FIXED_WIDTH;
    
    director->setContentScaleFactor(resourceSize.width / designSize.width);
    glview->setDesignResolutionSize(designSize.width, designSize.height, policy);
    
    // turn on display FPS
    director->setDisplayStats(true);

    // appC cloud 開始
    AppCCloudPlugin::setMK_iOS(Constant::APPC_MEDIA_KEY()).start();
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // 音楽設定
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.3);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3);
    
    // テクスチャアトラスを読み込む
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("character/enemy/enemy.plist");
    frameCache->addSpriteFramesWithFile("character/persona/persona.plist");
    frameCache->addSpriteFramesWithFile("misc/misc.plist");
    frameCache->addSpriteFramesWithFile("bg/bg.plist");

    frameCache->addSpriteFramesWithFile("effect/battleEffect0.plist");
    if (GameManager::getInstance()->isScreenModeHd())
    {
        frameCache->addSpriteFramesWithFile("effect/battleEffect1.plist");
    }

    // ゲームデータが存在するか判定し、存在しない場合は初期セットアップを行う
    if (!UserDataStore::getInstance()->isDataStored())
    {
        CCLOG("appdelegate: datastore-NG");
        UserDataStore::getInstance()->setupData();
    }
    
    // CocosBuilderのファイルを読み込みゲーム画面を生成する
    auto *pScene = TitleSceneLoader::createScene();
    
    // run
    director->runWithScene(pScene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}
