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
    int battleRank = GameManager::getInstance()->getBattleRank();
    StringMapVector charaRankList = UserDataStore::getInstance()->getRankList();
    int score = GameManager::getInstance()->battleDamagePoint;
    int burstCount = GameManager::getInstance()->burstCount;
    
    // データ保存（アプリ内）
    saveData(battleRank, charaRankList, score, burstCount);

    // データ保存（Gamers内）
    saveGamers();
    
    // スコア表示
    displayInfo(battleRank, charaRankList, score, burstCount);
}

void ResultScene::saveData(int battleRank, StringMapVector charaRankList, int score, int burstCount)
{
    auto store = UserDataStore::getInstance();
    
    // バトル回数
    store->setBattleCount(store->getBattleCount() + 1);
    
    // キャラクターランク
    std::string key = Constant::charaKey(GameManager::getInstance()->charaSelect);
    std::string charaRank = charaRankList[0][key];
    charaRankList[0][key] = std::to_string(std::stoi(charaRankList[0][key]) + 1);
    store->setRankList(charaRankList);
    
    // トータルランク
    int totalRank = 0;
    for (int idx = Constant::CharaSelectStart; idx <= Constant::CharaSelectEnd; idx++)
    {
        std::string key = Constant::charaKey((Constant::CharaSelect)idx);
        totalRank += std::stoi(charaRankList[0][key]);
        CCLOG("totalRank: %d", totalRank);
    }
    store->setTotalRank(totalRank);

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

void ResultScene::saveGamers()
{
    auto store = UserDataStore::getInstance();
    
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_BATTLE_COUNT, store->getBattleCount());
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_TOTAL_RANK, store->getTotalRank());
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_TOTAL_SCORE, store->getTotalScore());
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_TOTAL_BURST, store->getTotalBurst());
    
    StringMap charaRankList = store->getRankList()[0];
    std::string key;
    key = Constant::charaKey(Constant::CharaSelect::Conoha);
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_RANK_CONOHA, std::stoi(charaRankList[key]));
    key = Constant::charaKey(Constant::CharaSelect::Anzu);
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_RANK_ANZU, std::stoi(charaRankList[key]));
};

void ResultScene::displayInfo(int battleRank, StringMapVector charaRankList, int score, int burstCount)
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
    std::string charaName = Constant::charaName(GameManager::getInstance()->charaSelect);
    std::string key = Constant::charaKey(GameManager::getInstance()->charaSelect);
    std::string charaRank = charaRankList[0][key];
    
    relativeLabelHeight = 8.0f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("BATTLE RESULT", point, Constant::LARGE_FONT());
    resultLabel->setScale(BM_FONT_SIZE64(16));
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight = 6.5f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("トータルランク: " + std::to_string(battleRank), point);
    resultLabel->setScale(BM_FONT_SIZE64(20));
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight -= .6f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create(charaName + "のランク: " + charaRank, point);
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

    relativeLabelHeight -= 1.0f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("+1 ランクアップ！", point);
    resultLabel->setScale(BM_FONT_SIZE64(32));
    this->addChild(resultLabel, ZOrder::Font);
};


void ResultScene::tappedSocialButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedSocialButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");

    //ツイート画面呼び出し
    NativeLauncher::openTweetDialog("10sec BURST!【ランク 27｜スコア 9,999pt｜ブレイク 1回】 http://~ #mikumoburst");
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

//    //    int index = arc4random() % 2;
//    int index = arc4random() % 4;
//    switch(index){
//        case 0:
//            // マッチアップバナー表示（左上）
//            AppCCloudPlugin::Ad::showMatchAppView(AppCCloudPlugin::LEFT, AppCCloudPlugin::TOP);
//            break;
//        case 1:
//            // マッチアップバナー表示 (右上)
//            AppCCloudPlugin::Ad::showMatchAppView(AppCCloudPlugin::RIGHT, AppCCloudPlugin::TOP);
//            break;
//        case 2:
//            // マッチアップバナー表示 (右下)
//            AppCCloudPlugin::Ad::showMatchAppView(AppCCloudPlugin::RIGHT, AppCCloudPlugin::BOTTOM);
//            break;
//        case 3:
//            // マッチアップバナー表示 (左下)
//            AppCCloudPlugin::Ad::showMatchAppView(AppCCloudPlugin::LEFT, AppCCloudPlugin::BOTTOM);
//            break;
//        default:
//            // マッチアップバナー消去
//            AppCCloudPlugin::Ad::hideMatchAppView();
//            break;
//    }
    
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
