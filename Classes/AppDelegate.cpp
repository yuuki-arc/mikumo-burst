#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "TitleScene.h"

USING_NS_CC;

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
    
    glview->setDesignResolutionSize(320, 480, ResolutionPolicy::SHOW_ALL);
    
    Size frameSize = glview->getFrameSize();   //画面サイズ取得
    std::vector<std::string> searchPath;
    
    //デバイスの縦幅が960px以上の場合は、２倍サイズの画像リソースを使用する
    if (frameSize.height >= 960.0f ) {
        searchPath.push_back("hd");
        director->setContentScaleFactor(2.0f);
    } else {
        searchPath.push_back("sd");
    }
    FileUtils::getInstance()->setSearchPaths(searchPath);
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    auto scene = Title::createScene();
    
    // run
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
