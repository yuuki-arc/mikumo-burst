#include "SelectScene.h"
#include "ScoreSceneLoader.h"
#include "BattleSceneLoader.h"
#include "GoogleAnalyticsTracker.h"
#include "AppCCloudPlugin.h"
#include "Constant.h"
#include "GameManager.h"
#include "CharacterCreator.h"
#include "SoundManager.h"
#include "TextCreator.h"
#include "UserDataStore.h"

SelectScene::SelectScene()
: personaImageList(Constant::PERSONA_IMAGE_LIST())
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
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBattleButton", SelectScene::tappedBattleButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBossButton", SelectScene::tappedBossButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedScoreButton", SelectScene::tappedScoreButton);
    return NULL;
}

void SelectScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    // BGM
    SoundManager* soundManager = new SoundManager();
    soundManager->playBGM("bgm_title", true);
    
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
    
    // キャラ
    int num = 1; //CCRANDOM_0_1() * personaImageList.size();
    std::string personaFileName = StringUtils::format("%s.png", personaImageList.at(num).c_str());
    Point position = Point(origin.x + visibleSize.width * 2 / 3,
                           origin.y + visibleSize.height * 6 / 10);
    
    CharacterCreator* creator = new CharacterCreator();
    creator->init(CharacterScale::HARF);
    Sprite* character = creator->create(personaFileName, position);
    this->addChild(character, ZOrder::Persona);
    
    // メニュー表示
    Sprite* windowSprite = Sprite::createWithSpriteFrameName("menu_window.png");
    windowSprite->setPosition(Point(origin.x + visibleSize.width / 2,
                                    origin.y + visibleSize.height * 41 / 100));
    windowSprite->setScale(windowSprite->getScale(),
                           windowSprite->getScale() * 32 / 100);
    addChild(windowSprite, ZOrder::Menu);
    
    // データを取得
    int battleRank = GameManager::getInstance()->getBattleRank();
    auto store = UserDataStore::getInstance();
    
    // 次回バトルランク表示
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
    resultLabel = TextCreator::create(std::to_string(battleRank), point, Constant::LARGE_FONT());
    resultLabel->setScale(BM_FONT_SIZE64(32));
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight = 5.0f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("総合戦績 ", point);
    resultLabel->setColor(Color3B(113, 212, 255));
    this->addChild(resultLabel, ZOrder::Font);
    
    // スコア表示
    labelWidth = origin.x + visibleSize.width * 15 / 100;
    
    relativeLabelHeight -= .5f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("バトル回数: " + std::to_string(store->getBattleCount()) + " 回", point);
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight -= .4f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("最高バトルランク: " + std::to_string(store->getHighRank()), point);
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
