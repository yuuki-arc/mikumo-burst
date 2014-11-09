#include "ResultScene.h"
#include "SelectSceneLoader.h"
#include "Constant.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "TextCreator.h"
#include "UserDataStore.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

bool ResultScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

    return true;
}

SEL_MenuHandler ResultScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);

    return NULL;
}

Control::Handler ResultScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedSelectButton", ResultScene::tappedSelectButton);
    return NULL;
}

void ResultScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    // BGM
    SoundManager* soundManager = new SoundManager();
    soundManager->playBGM("bgm_result", true);

    // SE
    soundManager->preloadSE("se_select");

    // スコア計算
    int currentRank = UserDataStore::getInstance()->getRank();
    int score = GameManager::getInstance()->battleDamagePoint;
    int ebCount = GameManager::getInstance()->battleEternityPoint;
    
    // スコア表示
    float labelWidth = origin.x + visibleSize.width * 1/ 10;
    float relativeLabelHeight = 9.5f;
    Label* resultLabel;
    Point point;
    
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("RESULT", point, Color3B(113, 212, 255));
    this->addChild(resultLabel, ZOrder::Font);

    relativeLabelHeight -= 1.0f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("RANK: " + std::to_string(currentRank), point);
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight -= 1.0f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("SCORE: " + std::to_string(score), point);
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight -= 1.0f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("BREAK: " + std::to_string(ebCount), point);
    this->addChild(resultLabel, ZOrder::Font);
    
    // 次ランクへ
    if (currentRank < Constant::LIMIT_RANK)
    {
        currentRank++;
        UserDataStore::getInstance()->setRank(currentRank);
        CCLOG("Result - rank:%d", UserDataStore::getInstance()->getRank());
    }
    
    
    // スコア保存
    StringMapVector scoreList = UserDataStore::getInstance()->getHighScore();
    StringMap scoreMap;
    scoreMap.insert(std::make_pair("score", std::to_string(score)));
    scoreMap.insert(std::make_pair("break", std::to_string(ebCount)));
    scoreList.push_back(scoreMap);
    UserDataStore::getInstance()->setHighScore(scoreList);

//    Label* resultLabel = Label::createWithBMFont("Arial_Black.fnt", UserDataStore::getInstance()->getHighScore());
//    resultLabel->setAnchorPoint(Point(0.5, 0.5));
//    resultLabel->setPosition(Point(origin.x + visibleSize.width * 1/ 10,
//                                  origin.y + visibleSize.height * 9.5 / 10));
//    resultLabel->getTexture()->setAliasTexParameters();
//    this->addChild(resultLabel, ZOrder::Font);
    
}

void ResultScene::tappedSelectButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedSelectButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");

    Scene* scene = SelectSceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}
