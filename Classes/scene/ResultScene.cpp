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
    int tap = GameManager::getInstance()->battleDamagePoint;
    int burstCount = GameManager::getInstance()->burstCount;
    int score = tap * 1000;//+ボーナス
    
    // データ保存（アプリ内）
    saveData(battleRank, charaRankList, tap, burstCount, score);

    // データ保存（Gamers内）
    saveGamers();
    
    // スコア表示
    displayInfo(battleRank, charaRankList, tap, burstCount, score);
}

void ResultScene::saveData(int battleRank, StringMapVector charaRankList, int tap, int burstCount, int score)
{
    auto store = UserDataStore::getInstance();
    
    // バトル回数
    store->setBattleCount(store->getBattleCount() + 1);
    
    // キャラクターランク
    if (GameManager::getInstance()->isBattleModeNormal())
    {
        // 通常バトル時のみランクアップする
        std::string charaRankKey = Constant::charaKey(GameManager::getInstance()->getCharaSelect());
        std::string charaRank = charaRankList[0][charaRankKey];
        charaRankList[0][charaRankKey] = std::to_string(std::stoi(charaRankList[0][charaRankKey]) + 1);
    }
    store->setRankList(charaRankList);
    
    // トータルランク
    int totalRank = 0;
    for (int idx = Constant::CharaSelectStart; idx <= Constant::CharaSelectEnd; idx++)
    {
        std::string totalRankKey = Constant::charaKey((Constant::CharaSelect)idx);
        totalRank += std::stoi(charaRankList[0][totalRankKey]);
    }
    store->setTotalRank(totalRank);

    // トータルタップ
    store->setTotalTap(store->getTotalTap() + tap);
    
    // トータルバースト
    store->setTotalBurst(store->getTotalBurst() + burstCount);

    // トータルスコア
    store->setTotalScore(store->getTotalScore() + score);
};

void ResultScene::saveGamers()
{
    auto store = UserDataStore::getInstance();
    
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_BATTLE_COUNT, store->getBattleCount());
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_TOTAL_RANK, store->getTotalRank());
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_TOTAL_TAP, store->getTotalTap());
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_TOTAL_BURST, store->getTotalBurst());
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_TOTAL_SCORE, store->getTotalScore());
    
    StringMap charaRankList = store->getRankList()[0];
    std::string key;
    key = Constant::charaKey(Constant::CharaSelect::Conoha);
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_RANK_CONOHA, std::stoi(charaRankList[key]));
    key = Constant::charaKey(Constant::CharaSelect::Anzu);
    AppCCloudPlugin::Gamers::setLeaderBoard(Constant::LEADERBOARD_RANK_ANZU, std::stoi(charaRankList[key]));
};

void ResultScene::displayInfo(int battleRank, StringMapVector charaRankList, int tap, int burstCount, int score)
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
    if (GameManager::getInstance()->isBattleModeBoss())
    {
        point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
        resultLabel = TextCreator::create("トータルランク: " + std::to_string(battleRank), point);
        resultLabel->setScale(BM_FONT_SIZE64(20));
        this->addChild(resultLabel, ZOrder::Font);
    }
    
    relativeLabelHeight -= .6f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("タップ: " + std::to_string(tap) + " TAP", point);
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
    
    if (GameManager::getInstance()->isBattleModeNormal())
    {
        // 通常バトル時はキャラクターランクを表示
        std::string charaName = Constant::charaName(GameManager::getInstance()->getCharaSelect());
        std::string key = Constant::charaKey(GameManager::getInstance()->getCharaSelect());
        std::string charaRank = charaRankList[0][key];
        
        relativeLabelHeight -= .6f;
        point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
        resultLabel = TextCreator::create(charaName + "のランク: " + charaRank, point);
        resultLabel->setScale(BM_FONT_SIZE64(20));
        this->addChild(resultLabel, ZOrder::Font);
        
        relativeLabelHeight -= 1.0f;
        point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
        resultLabel = TextCreator::create("ランク+1 アップ !", point);
        resultLabel->setScale(BM_FONT_SIZE64(32));
        this->addChild(resultLabel, ZOrder::Font);
    }
    else
    {
        // ボスバトル時は固定テキストを表示
        relativeLabelHeight -= 1.0f;
        point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
        resultLabel = TextCreator::create("ボスに挑戦した !", point);
        resultLabel->setScale(BM_FONT_SIZE64(32));
        this->addChild(resultLabel, ZOrder::Font);
    }
};


void ResultScene::tappedSocialButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedSocialButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");

    //ツイート画面呼び出し
    const string DATAKEY_STR("tweet_text");

    std::string strSrc = "10sec BURST!【ランク 27｜スコア 9,999pt｜ブレイク 1回】 http://~ #mikumoburst";
    AppCCloudPlugin::Data::setDataStore(DATAKEY_STR, strSrc);
    
    DataStoreData tweetText = AppCCloudPlugin::Data::getDataStore(DATAKEY_STR);
    std::string str = tweetText.getText();
    NativeLauncher::openTweetDialog(str.c_str());
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
}
