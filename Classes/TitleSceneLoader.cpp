#include "TitleSceneLoader.h"

Scene* TitleSceneLoader::createScene()
{
    cocosbuilder::NodeLoaderLibrary* nodeLoaderLibrary = cocosbuilder::NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
    nodeLoaderLibrary->registerNodeLoader("TitleScene", TitleSceneLoader::loader());
    
    cocosbuilder::CCBReader* ccbReader = new cocosbuilder::CCBReader(nodeLoaderLibrary);
    Node* node = ccbReader->readNodeGraphFromFile("TitleScene.ccbi");
    
    Scene* pScene = Scene::create();
    if (node != NULL)
    {
        pScene->addChild(node);
        
        auto director = Director::getInstance();
        auto glview = director->getOpenGLView();
        if(!glview) {
            glview = GLView::create("My Game");
            director->setOpenGLView(glview);
        }
        Size screenSize = glview->getFrameSize();
        
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();

//        // 背景
//        Sprite* background = Sprite::create("04.png");
//        background->setPosition(Point(origin.x + visibleSize.width / 2,
//                                      origin.y + visibleSize.height / 2));
//        pScene->addChild(background, 0);
        
        // エフェクト
        ParticleSystemQuad* particle1 = ParticleSystemQuad::create("title_particle1.plist");
        particle1->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
        pScene->addChild(particle1);
        ParticleSystemQuad* particle2 = ParticleSystemQuad::create("title_particle2.plist");
        particle2->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
        pScene->addChild(particle2);
    }
    ccbReader->release();
    
    return pScene;
}
