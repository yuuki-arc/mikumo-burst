#include "SelectScene.h"
#include "ScoreSceneLoader.h"
#include "BattleSceneLoader.h"
#include "CharacterCreator.h"
#include "SoundManager.h"
#include "TextCreator.h"
#include "UserDataStore.h"

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

bool SelectScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	return true;
}

SEL_MenuHandler SelectScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    return NULL;
}

Control::Handler SelectScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBattleButton", SelectScene::tappedBattleButton);
    return NULL;
}

void SelectScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    // BGM
    SoundManager* soundManager = new SoundManager();
    soundManager->playBGM("bgm_title", true);
    
    // SE
    soundManager->preloadSE("se_select");

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    // データを取得
    int currentRank = UserDataStore::getRank(1);
    CCLOG("Select - rank:%d", currentRank);
    StringMapVector scoreList = UserDataStore::getHighScore();
    
    // スコア表示
    float labelWidth = origin.x + visibleSize.width * 1/ 10;
    float relativeLabelHeight = 8.0f;
    Label* resultLabel;
    Point point;

    relativeLabelHeight = 8.0f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("LEVEL: " + std::to_string(currentRank), point);
    this->addChild(resultLabel, ZOrder::Font);

    for (StringMapVector::iterator it = scoreList.begin(); it != scoreList.end(); it++)
    {
        StringMap map = (*it);
        
        relativeLabelHeight = 7.0f;
        point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
        resultLabel = TextCreator::create("SCORE: " + map["chain"], point);
        this->addChild(resultLabel, ZOrder::Font);
        
        relativeLabelHeight = 6.0f;
        point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
        resultLabel = TextCreator::create("BREAK: " + map["break"], point);
        this->addChild(resultLabel, ZOrder::Font);
        
        break;
    }

    
    // キャラ
//    int num = 5; //CCRANDOM_0_1() * personaImageList.size();
//    std::string personaFileName = StringUtils::format("%s.png", personaImageList.at(num).c_str());
//    
//    CharacterCreator* creator = new CharacterCreator();
//    Sprite* character = creator->create(personaFileName, CharacterScale::HARF);
//    this->addChild(character, ZOrder::Persona);
}

void SelectScene::tappedBattleButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedBattleButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    
    Scene* scene = BattleSceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}
