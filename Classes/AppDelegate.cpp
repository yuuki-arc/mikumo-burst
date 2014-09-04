#include "AppDelegate.h"
#include "extensions/cocos-ext.h"

#include "GameManager.h"
#include "TitleScene.h"
#include "TitleSceneLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

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
    
    Size designSize = Size(320, 480); // ベースサイズ
    Size resourceSize;
    Size screenSize = glview->getFrameSize();   //画面サイズ取得
    
    std::vector<std::string> searchPaths;
    std::vector<std::string> resDirOrders;

    searchPaths.push_back("Resources");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
    CCLOG("height: %f, witdh: %f", screenSize.width, screenSize.height);

    if (screenSize.height >= 960) {
        resourceSize = Size(640, 960);
        resDirOrders.push_back("resources-iphonehd");
        GameManager::getInstance()->screenMode = ScreenModeHd;
    } else {
        resourceSize = Size(320, 480);
        resDirOrders.push_back("resources-iphone");
        GameManager::getInstance()->screenMode = ScreenModeSd;
    }
    
    FileUtils::getInstance()->setSearchPaths(resDirOrders);
    
    director->setContentScaleFactor(resourceSize.width / designSize.width);
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // テクスチャアトラスを読み込む
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("character/enemy/enemy.plist");
    frameCache->addSpriteFramesWithFile("character/persona/persona.plist");
    
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
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
