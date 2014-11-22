#include "scene/TitleSceneLoader.h"

Scene* TitleSceneLoader::createScene()
{
    CCLOG("TitleSceneLoader::createScene");

    cocosbuilder::NodeLoaderLibrary* nodeLoaderLibrary = cocosbuilder::NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
    nodeLoaderLibrary->registerNodeLoader("TitleScene", TitleSceneLoader::loader());
    
    cocosbuilder::CCBReader* ccbReader = new cocosbuilder::CCBReader(nodeLoaderLibrary);
    Node* node = ccbReader->readNodeGraphFromFile("TitleScene.ccbi");
    
    Scene* pScene = Scene::create();
    if (node != NULL)
    {
        pScene->addChild(node);
        
    }
    ccbReader->release();
    
    return pScene;
}
