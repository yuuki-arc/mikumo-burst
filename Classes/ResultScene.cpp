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
    // BGM
    SoundManager* soundManager = new SoundManager();
    soundManager->playBGM("bgm_result", true);

    // SE
    soundManager->preloadSE("se_select");

    // データ取得
    int rank = UserDataStore::getInstance()->getRank();
    int score = GameManager::getInstance()->battleDamagePoint;
    int breakCount = GameManager::getInstance()->battleEternityPoint;
    
    // データ保存
    saveData(rank, score, breakCount);

    // スコア表示
    displayInfo(rank, score, breakCount);
    
}

void ResultScene::saveData(int rank, int score, int breakCount)
{
    auto store = UserDataStore::getInstance();
    
    // 現在ランク
    store->setRank(rank);
    
    // 最高ランク
    if (store->getHighRank() < rank)
    {
        store->setHighRank(rank);
    };

    // トータルスコア
    store->setTotalScore(store->getTotalScore() + score);
    
    // トータルブレイク
    store->setTotalBreak(store->getTotalBreak() + breakCount);
    
    // スコアテーブル
    const std::string KEY_RANK = Constant::UserDefaultKey::SCORE_TABLE_RANK();
    const std::string KEY_SCORE = Constant::UserDefaultKey::SCORE_TABLE_SCORE();
    const std::string KEY_BREAK = Constant::UserDefaultKey::SCORE_TABLE_BREAK();
    
    StringMapVector scoreList = store->getScoreTable();
    StringMap scoreMap;
    scoreMap.insert(std::make_pair(KEY_RANK, std::to_string(rank)));
    scoreMap.insert(std::make_pair(KEY_SCORE, std::to_string(score)));
    scoreMap.insert(std::make_pair(KEY_BREAK, std::to_string(breakCount)));
    scoreList.push_back(scoreMap);
    store->setScoreTable(scoreList);
};

void ResultScene::displayInfo(int rank, int score, int breakCount)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // メニュー表示
    Sprite* windowSprite = Sprite::createWithSpriteFrameName("menu_window.png");
    windowSprite->setPosition(Point(origin.x + visibleSize.width / 2,
                                    origin.y + visibleSize.height * 48 / 100));
    windowSprite->setScale(windowSprite->getScale(),
                           windowSprite->getScale() * 6 / 10);
    addChild(windowSprite, ZOrder::Menu);

    // スコア表示
    float labelWidth = origin.x + visibleSize.width * 1 / 10;
    float relativeLabelHeight;
    Label* resultLabel;
    Point point;
    
    relativeLabelHeight = 8.0f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("BATTLE RESULT", point, Constant::LARGE_FONT());
    resultLabel->setScale(BM_FONT_SIZE64(16));
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight = 6.5f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("バトルランク: " + std::to_string(rank), point);
    resultLabel->setScale(BM_FONT_SIZE64(20));
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight -= .6f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("スコア: " + std::to_string(score) + " pt", point);
    resultLabel->setScale(BM_FONT_SIZE64(20));
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight -= .6f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("ブレイク: " + std::to_string(breakCount) + " 回", point);
    resultLabel->setScale(BM_FONT_SIZE64(20));
    this->addChild(resultLabel, ZOrder::Font);
};

void ResultScene::tappedSelectButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedSelectButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");

    Scene* scene = SelectSceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}
