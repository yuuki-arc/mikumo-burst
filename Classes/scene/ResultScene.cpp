#include "scene/ResultScene.h"
#include "scene/SelectSceneLoader.h"
#include "tools/GoogleAnalyticsTracker.h"
#include "tools/AppCCloudPlugin.h"
#include "core/Constant.h"
#include "core/GameManager.h"
#include "resources/SoundManager.h"
#include "factory/TextCreator.h"
#include "resources/UserDataStore.h"
#include "tools/NativeLauncher.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

bool ResultScene::init()
{
    GoogleAnalyticsTracker::sendScreen("ResultScene");
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
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedSocialButton", ResultScene::tappedSocialButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedRewardButton", ResultScene::tappedRewardButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedMoreGamesButton", ResultScene::tappedMoreGamesButton);
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
    int burstCount = GameManager::getInstance()->burstCount;
    
    // データ保存（アプリ内）
    saveData(rank, score, burstCount);

    // データ保存（Gamers内）
    saveGamers(rank, score, burstCount);
    
    // スコア表示
    displayInfo(rank, score, burstCount);
}

void ResultScene::saveData(int rank, int score, int burstCount)
{
    auto store = UserDataStore::getInstance();
    
    // バトル回数
    store->setBattleCount(store->getBattleCount() + 1);
    
    // 現在ランク
    store->setRank(rank + 1);
    
    // 最高ランク
    if (store->getHighRank() < rank)
    {
        store->setHighRank(rank);
    };

    // トータルスコア
    store->setTotalScore(store->getTotalScore() + score);
    
    // トータルバースト
    store->setTotalBurst(store->getTotalBurst() + burstCount);
    
//    // スコアテーブル
//    const std::string KEY_RANK = Constant::UserDefaultKey::SCORE_TABLE_RANK();
//    const std::string KEY_SCORE = Constant::UserDefaultKey::SCORE_TABLE_SCORE();
//    const std::string KEY_BURST = Constant::UserDefaultKey::SCORE_TABLE_BURST();
//    
//    StringMapVector scoreList = store->getScoreTable();
//    StringMap scoreMap;
//    scoreMap.insert(std::make_pair(KEY_RANK, std::to_string(rank)));
//    scoreMap.insert(std::make_pair(KEY_SCORE, std::to_string(score)));
//    scoreMap.insert(std::make_pair(KEY_BURST, std::to_string(burstCount)));
//    scoreList.push_back(scoreMap);
//    store->setScoreTable(scoreList);
};

void ResultScene::saveGamers(int rank, int score, int burstCount)
{
    auto store = UserDataStore::getInstance();
    
    // バトル回数
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_BATTLE_COUNT,
                                            store->getBattleCount());

    // 最高ランク
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_BATTLE_RANK,
                                            store->getHighRank());
    
    // トータルスコア
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_TOTAL_SCORE,
                                            store->getTotalScore());
    
    // トータルバースト
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_TOTAL_BURST,
                                            store->getTotalBurst());
    
};

void ResultScene::displayInfo(int rank, int score, int burstCount)
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
    resultLabel = TextCreator::create("アタック: " + std::to_string(score) + " HIT", point);
    resultLabel->setScale(BM_FONT_SIZE64(20));
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight -= .6f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("バースト: " + std::to_string(burstCount) + " 回", point);
    resultLabel->setScale(BM_FONT_SIZE64(20));
    this->addChild(resultLabel, ZOrder::Font);

    relativeLabelHeight -= .6f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("スコア: " + std::to_string(score) + " pt", point);
    resultLabel->setScale(BM_FONT_SIZE64(20));
    this->addChild(resultLabel, ZOrder::Font);
};


void ResultScene::tappedSocialButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedSocialButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");

    //ツイート画面呼び出し
    NativeLauncher::openTweetDialog("10sec BURST!【ランク 27｜スコア 9,999pt｜ブレイク 1回】 http://~ #10sec_burst");
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

void ResultScene::tappedRewardButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedRewardButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    
    //　ポイント画面表示処理
    AppCCloudPlugin::Reward::openRewardPointView();
}

void ResultScene::tappedMoreGamesButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedMoreGamesButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    
    // 広告リスト型表示
    AppCCloudPlugin::Ad::openAdListView();

//    // シンプル型表示
//    int index = arc4random() % 2;
//    switch(index){
//        case 0:
//            // シンプル表示（上側）
//            AppCCloudPlugin::Ad::showSimpleView(AppCCloudPlugin::TOP);
//            break;
//        case 1:
//            // シンプル表示 (下側)
//            AppCCloudPlugin::Ad::showSimpleView(AppCCloudPlugin::BOTTOM);
//            break;
//        default:
//            // シンプル消去
//            AppCCloudPlugin::Ad::hideSimpleView();
//            break;
//    }
}
