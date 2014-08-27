#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "TitleScene.h"
#include "cocos-ext.h"
#include "editor-support/cocosbuilder/CocosBuilder.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    
//    glview->setDesignResolutionSize(320, 480, ResolutionPolicy::SHOW_ALL);
//    
//    Size frameSize = glview->getFrameSize();   //画面サイズ取得
//    std::vector<std::string> searchPath;
//    
//    //デバイスの縦幅が960px以上の場合は、２倍サイズ画像リソースを使用する
//    if (frameSize.height >= 960.0f ) {
//        searchPath.push_back("hd");
//        director->setContentScaleFactor(2.0f);
//    } else {
//        searchPath.push_back("sd");
//    }
//    FileUtils::getInstance()->setSearchPaths(searchPath);

    /* ここから追加コード */
    
    Size designSize = Size(320, 480); // ベースサイズ
    Size resourceSize;
    Size screenSize = glview->getFrameSize();   //画面サイズ取得
    
    std::vector<std::string> searchPaths;
    std::vector<std::string> resDirOrders;
    
    Platform platform = Application::getTargetPlatform();
    if (platform == Platform::OS_IPHONE || platform == Platform::OS_IPAD) {
        searchPaths.push_back("Published-iOS");
        FileUtils::getInstance()->setSearchPaths(searchPaths);
        
        if (screenSize.width > 768) {
            resourceSize = Size(1536, 2048);
            resDirOrders.push_back("resources-ipadhd");
        } else if (screenSize.width > 640) {
            resourceSize = Size(768, 1536);
            resDirOrders.push_back("resources-ipad");
        } else if (screenSize.width > 480) {
            if (screenSize.height < 1536) {
                // 4インチ
                resourceSize = Size(640, 1136);
            } else {
                // 3.5インチ
                resourceSize = Size(640, 960);
            }
            resDirOrders.push_back("resources-iphonehd");
        } else {
            resourceSize = Size(320, 480);
            resDirOrders.push_back("resources-iphone");
        }
        
        FileUtils::getInstance()->setSearchPaths(resDirOrders);
    } else if (platform == Platform::OS_ANDROID) {
        if (screenSize.width > 1200) {
            resourceSize = Size(800, 1200);
            resDirOrders.push_back("resources-xlarge");
        } else if (screenSize.width > 960) {
            resourceSize = Size(640, 960);
            resDirOrders.push_back("resources-large");
        } else if (screenSize.width > 480) {
            resourceSize = Size(480, 720);
            resDirOrders.push_back("resources-medium");
        } else {
            resourceSize = Size(320, 568);
            resDirOrders.push_back("resources-small");
        }
        
        FileUtils::getInstance()->setSearchPaths(resDirOrders);
    }
    
    director->setContentScaleFactor(resourceSize.width / designSize.width);
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::FIXED_HEIGHT);
    
    /* ここまでが追加コード */
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
//    // create a scene. it's an autorelease object
//    auto scene = Title::createScene();
    
//    // run
//    director->runWithScene(scene);
    
    NodeLoaderLibrary *lib = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
    CCBReader *reader = new CCBReader(lib);
    auto *scene = reader->createSceneWithNodeGraphFromFile("TitleScene.ccbi");
    director->runWithScene(scene);

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
