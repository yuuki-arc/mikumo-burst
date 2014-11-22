#include "scene/ResultSceneLoader.h"

Scene* ResultSceneLoader::createScene()
{
    cocosbuilder::NodeLoaderLibrary* nodeLoaderLibrary = cocosbuilder::NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
    nodeLoaderLibrary->registerNodeLoader("ResultScene", ResultSceneLoader::loader());
    
    cocosbuilder::CCBReader* ccbReader = new cocosbuilder::CCBReader(nodeLoaderLibrary);
    Node* node = ccbReader->readNodeGraphFromFile("ResultScene.ccbi");
    
    Scene* pScene = Scene::create();
    if (node != NULL)
    {
        pScene->addChild(node);
    }
    ccbReader->release();
    
    return pScene;
}
