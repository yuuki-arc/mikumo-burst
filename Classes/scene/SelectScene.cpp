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
    
    // Voice
    Constant::StringVector list = Constant::VOICE_LIST(Constant::Voice::Ready);
    Constant::StringVector::const_iterator iterator = list.begin();
    while (iterator != list.end()) {
        soundManager->preloadVoice(*iterator);
        CCLOG("preloadVoice:%s", (*iterator).c_str());
        iterator++;
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
    Point position = Point(origin.x + visibleSize.width * 2 / 3,
                           origin.y + visibleSize.height * 6 / 10);
    
    CharacterCreator* creator = new CharacterCreator();
    creator->init(CharacterScale::HARF);
    Sprite* character = creator->create(personaFileName, position);
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
    resultLabel = TextCreator::create("次のバトルランク: ", point);
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight -= 1.0f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create(rank, point, Constant::LARGE_FONT());
    resultLabel->setScale(BM_FONT_SIZE64(32));
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
    resultLabel = TextCreator::create("最高ランク: " + std::to_string(store->getHighRank()), point);
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
    // キャラクタ切り替え
    Constant::StringVector personaList = Constant::PERSONA_IMAGE_LIST(Constant::ImagePersona::PersonaSelect);
    int num = GameManager::getInstance()->charaSelect;
    std::string personaFileName = StringUtils::format("%s.png", personaList[num].c_str());
    
    Sprite* character = (Sprite*)this->getChildByTag(Tag::Character);
    CharacterCreator* creator = new CharacterCreator();
    creator->init(CharacterScale::HARF);
    creator->change(character, personaFileName);

    // ランク切り替え
    auto store = UserDataStore::getInstance();
    StringMap rankList = store->getRankList()[0];
    std::string key = Constant::charaKey(GameManager::getInstance()->charaSelect);
    std::string rank = rankList[key];

    Label* label = (Label*)this->getChildByTag(Tag::Rank);
    label->setString(rank);
}

void SelectScene::tappedChangeButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedChangeButton eventType = %d", pControlEventType);

    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");

    if (GameManager::getInstance()->isCharaSelectConoha())
    {
        GameManager::getInstance()->charaSelect = Constant::Anzu;
    }
    else
    {
        GameManager::getInstance()->charaSelect = Constant::Conoha;
    }
    
    int num = arc4random() % 2;
    Constant::StringVector list = Constant::VOICE_LIST(Constant::Voice::Ready);
    
    soundManager->playSE("se_select");
    soundManager->playVoice(list[num]);
    soundManager->stopBGM();

    changeCharacter();
}

void SelectScene::tappedBattleButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedBattleButton eventType = %d", pControlEventType);
    GameManager::getInstance()->battleMode = BattleModeNormal;
    
    int num = arc4random() % 2;
    Constant::StringVector list = Constant::VOICE_LIST(Constant::Voice::Ready);
    
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
    
    int num = arc4random() % 2;
    Constant::StringVector list = Constant::VOICE_LIST(Constant::Voice::Ready);
    
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    soundManager->playVoice(list[num]);
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
