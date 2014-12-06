#include "scene/SelectScene.h"
#include "scene/ScoreSceneLoader.h"
#include "scene/BattleSceneLoader.h"
#include "tools/GoogleAnalyticsTracker.h"
#include "tools/AppCCloudPlugin.h"
#include "core/Constant.h"
#include "core/GameManager.h"
#include "factory/CharacterCreator.h"
#include "resources/SoundManager.h"
#include "factory/TextCreator.h"
#include "resources/UserDataStore.h"

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

bool SelectScene::init()
{
    GoogleAnalyticsTracker::sendScreen("SelectScene");
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
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedChangeButton", SelectScene::tappedChangeButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBattleButton", SelectScene::tappedBattleButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBossButton", SelectScene::tappedBossButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedScoreButton", SelectScene::tappedScoreButton);
    return NULL;
}

void SelectScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    // BGM
    SoundManager* soundManager = new SoundManager();
    soundManager->playBGM("bgm_select", true);
    
    // SE
    soundManager->preloadSE("se_select");
    
    // Voice（全キャラクター読み込む）
    for (int idx = Constant::CharaSelectStart; idx <= Constant::CharaSelectEnd; idx++)
    {
        Constant::StringVector list = Constant::VOICE_LIST((Constant::CharaSelect)idx,
                                                           Constant::Voice::Ready);
        Constant::StringVector::const_iterator iterator = list.begin();
        while (iterator != list.end()) {
            soundManager->preloadVoice(*iterator);
            CCLOG("preloadVoice:%s", (*iterator).c_str());
            iterator++;
        }
    }
 
    // 情報表示
    displayInfo();
}

void SelectScene::displayInfo()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // メニュー表示
    Sprite* windowSprite = Sprite::createWithSpriteFrameName("menu_window.png");
    windowSprite->setPosition(Point(origin.x + visibleSize.width / 2,
                                    origin.y + visibleSize.height * 41 / 100));
    windowSprite->setScale(windowSprite->getScale(),
                           windowSprite->getScale() * 32 / 100);
    addChild(windowSprite, ZOrder::Menu);
    
    // キャラクター表示
    Constant::StringVector personaList = Constant::PERSONA_IMAGE_LIST(Constant::ImagePersona::PersonaSelect);
    int num = GameManager::getInstance()->charaSelect;
    std::string personaFileName = StringUtils::format("%s.png", personaList[num].c_str());
    charaPos = Point(origin.x + visibleSize.width * 2 / 3,
                           origin.y + visibleSize.height * 6 / 10);
    
    CharacterCreator* creator = new CharacterCreator();
    creator->init(CharacterScale::HARF);
    Sprite* character = creator->create(personaFileName, charaPos);
    character->setTag(Tag::Character);
    this->addChild(character, ZOrder::Persona);
    
    // ランク表示
//    int rank = GameManager::getInstance()->getRank();
    auto store = UserDataStore::getInstance();
    StringMap rankList = store->getRankList()[0];
    std::string key = Constant::charaKey(GameManager::getInstance()->charaSelect);
    std::string rank = rankList[key];
    
    float labelWidth = origin.x + visibleSize.width * 1 / 10;
    float relativeLabelHeight;
    Label* resultLabel;
    Point point;
    
    relativeLabelHeight = 8.0f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    std::string charaName = Constant::charaName(GameManager::getInstance()->charaSelect);
    resultLabel = TextCreator::create(charaName + "のランク", point);
    resultLabel->setTag(Tag::RankStr);
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight -= 1.0f;
    point = Point(origin.x + visibleSize.width * 5 / 20,
                  origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create(rank, point, Constant::LARGE_FONT());
    resultLabel->setScale(BM_FONT_SIZE64(32));
    resultLabel->setAnchorPoint(Point(0.5f, 0.5f));
    resultLabel->setTag(Tag::Rank);
    this->addChild(resultLabel, ZOrder::Font);
    
    // 総合戦績表示
    relativeLabelHeight = 5.0f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("総合戦績 ", point);
    resultLabel->setColor(Color3B(113, 212, 255));
    this->addChild(resultLabel, ZOrder::Font);
    
    labelWidth = origin.x + visibleSize.width * 15 / 100;
    
    relativeLabelHeight -= .5f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("バトル回数: " + std::to_string(store->getBattleCount()) + " 回", point);
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight -= .4f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("トータルランク: " + std::to_string(store->getTotalRank()), point);
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight -= .4f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("トータルスコア: " + std::to_string(store->getTotalScore()) + " pt", point);
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight -= .4f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("トータルバースト: " + std::to_string(store->getTotalBurst()) + " 回", point);
    this->addChild(resultLabel, ZOrder::Font);
}

void SelectScene::changeCharacter()
{
    // 音声
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    Constant::StringVector list = Constant::VOICE_LIST(GameManager::getInstance()->charaSelect,
                                                       Constant::Voice::Select);
    int num = arc4random() % list.size();
    soundManager->playVoice(list[num]);

    // 切り替えアニメーション
    Sprite* character = (Sprite*)this->getChildByTag(Tag::Character);
    float marginX = character->getContentSize().width;
    float x = charaPos.x;
    float y = charaPos.y;
    character->runAction(
                     Sequence::create(
                                      MoveTo::create(0.2f, Point(-marginX, y)),
                                      CallFunc::create([character, x, y, marginX](){
                                          // キャラクタ切り替え
                                          Constant::StringVector personaList = Constant::PERSONA_IMAGE_LIST(Constant::ImagePersona::PersonaSelect);
                                          int num = GameManager::getInstance()->charaSelect;
                                          std::string personaFileName = StringUtils::format("%s.png", personaList[num].c_str());
                                          CharacterCreator* creator = new CharacterCreator();
                                          creator->init(CharacterScale::HARF);
                                          creator->change(character, personaFileName);
                                          character->setPosition(Point(x+marginX,y));
                                        }
                                      ),
                                      MoveTo::create(0.2f, Point(x, y)),
                                      nullptr
                                      )
                     );

    // ランクネーム切り替え
    Label* label;
    std::string charaName = Constant::charaName(GameManager::getInstance()->charaSelect);
    label = (Label*)this->getChildByTag(Tag::RankStr);
    label->setString(charaName + "のランク");
    
    // ランク切り替え
    auto store = UserDataStore::getInstance();
    StringMap rankList = store->getRankList()[0];
    std::string key = Constant::charaKey(GameManager::getInstance()->charaSelect);
    std::string rank = rankList[key];

    label = (Label*)this->getChildByTag(Tag::Rank);
    label->setString(rank);
}

void SelectScene::tappedChangeButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedChangeButton eventType = %d", pControlEventType);

    if (GameManager::getInstance()->isCharaSelectConoha())
    {
        GameManager::getInstance()->charaSelect = Constant::Anzu;
    }
    else
    {
        GameManager::getInstance()->charaSelect = Constant::Conoha;
    }

    changeCharacter();
}

void SelectScene::tappedBattleButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedBattleButton eventType = %d", pControlEventType);
    GameManager::getInstance()->battleMode = BattleModeNormal;
    
    // バトルランク設定（選択キャラ）
    auto store = UserDataStore::getInstance();
    StringMap rankList = store->getRankList()[0];
    std::string key = Constant::charaKey(GameManager::getInstance()->charaSelect);
    int battleRank = std::stoi(rankList[key]);
    GameManager::getInstance()->setBattleRank(battleRank);
    
    // 音声
    Constant::StringVector list = Constant::VOICE_LIST(GameManager::getInstance()->charaSelect,
                                                       Constant::Voice::Ready);
    int num = arc4random() % list.size();
    
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    soundManager->playVoice(list[num]);
    soundManager->stopBGM();
    
    Scene* scene = BattleSceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}

void SelectScene::tappedBossButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedBossButton eventType = %d", pControlEventType);
    GameManager::getInstance()->battleMode = BattleModeBoss;
    
    // バトルランク設定（合計値）
    auto store = UserDataStore::getInstance();
    StringMap rankList = store->getRankList()[0];
    int battleRank = 0;
    for (int idx = Constant::CharaSelectStart; idx <= Constant::CharaSelectEnd; idx++)
    {
        std::string key = Constant::charaKey((Constant::CharaSelect)idx);
        battleRank += std::stoi(rankList[key]);
    }
    GameManager::getInstance()->setBattleRank(battleRank);

    // 音声
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    for (int idx = Constant::CharaSelectStart; idx <= Constant::CharaSelectEnd; idx++)
    {
        Constant::StringVector list = Constant::VOICE_LIST((Constant::CharaSelect)idx,
                                                           Constant::Voice::Ready);
        int num = arc4random() % list.size();
        soundManager->playVoice(list[num]);
    }
    soundManager->stopBGM();
    
    Scene* scene = BattleSceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}

void SelectScene::tappedScoreButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedScoreButton eventType = %d", pControlEventType);
    
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    
//    Scene* scene = ScoreSceneLoader::createScene();
//    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
//    Director::getInstance()->replaceScene(trans);
    // GAMERS画面を開く
    AppCCloudPlugin::Gamers::showGamersView();

}
