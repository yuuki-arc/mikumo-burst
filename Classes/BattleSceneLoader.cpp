#include "BattleSceneLoader.h"
#include "GameManager.h"
#include "CharacterCreator.h"

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

        
        if (GameManager::getInstance()->isScreenModeHd())
        {
            background->setScale(background->getScale()*1.6, background->getScale()*1.6);
        }
        else
        {
            background->setScale(background->getScale()*0.8, background->getScale()*0.8);
        }
        pScene->addChild(background, -1);
        
        // キャラ
        CharacterCreator* creator = new CharacterCreator();
        Sprite* character = creator->create("f271.png", CharacterScale::ALL);
                
        pScene->addChild(character, -1);
    }
    ccbReader->release();

    //イベントリスナー作成
    auto listener = EventListenerTouchOneByOne::create();
    
    //イベントを飲み込むかどうか
    listener->setSwallowTouches(true);
    
    return pScene;
}
