#include "GameManager.h"
#include "BattleSceneLoader.h"

Scene* BattleSceneLoader::createScene()
{
    cocosbuilder::NodeLoaderLibrary* nodeLoaderLibrary = cocosbuilder::NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
    nodeLoaderLibrary->registerNodeLoader("BattleScene", BattleSceneLoader::loader());
    
    cocosbuilder::CCBReader* ccbReader = new cocosbuilder::CCBReader(nodeLoaderLibrary);
    Node* node = ccbReader->readNodeGraphFromFile("BattleScene.ccbi");
    
    Scene* pScene = Scene::create();
    if (node != NULL)
    {
        pScene->addChild(node);

        // 背景
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();
        
        Sprite* background = Sprite::create("bg/001-1.png");
        background->setPosition(Point(origin.x + visibleSize.width / 2,
                                      origin.y + visibleSize.height / 2));

        
        if (GameManager::sharedGameManager()->isScreenModeHd())
        {
            background->setScale(background->getScale()*1.6, background->getScale()*1.6);
        }
        else
        {
            background->setScale(background->getScale()*0.8, background->getScale()*0.8);
        }
        pScene->addChild(background, -1);
        
        // キャラ
        Sprite* character = Sprite::create("character/f271.png");
        character->setPosition(Point(origin.x + visibleSize.width / 2,
                                      origin.y + visibleSize.height * 6 / 10));
        if (GameManager::sharedGameManager()->isScreenModeSd())
        {
            character->setScale(character->getScale()/2, character->getScale()/2);
        }
        pScene->addChild(character, -1);
    }
    ccbReader->release();
    
    return pScene;
}
