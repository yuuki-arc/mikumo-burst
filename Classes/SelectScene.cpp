#include "SelectScene.h"
#include "ScoreSceneLoader.h"
#include "BattleSceneLoader.h"
#include "Constant.h"
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

    // 情報表示
    displayInfo();
}

void SelectScene::displayInfo()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // キャラ
    int num = 5; //CCRANDOM_0_1() * personaImageList.size();
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
                                    origin.y + visibleSize.height * 42 / 100));
    windowSprite->setScale(windowSprite->getScale(),
                           windowSprite->getScale() * 3 / 10);
    addChild(windowSprite, ZOrder::Menu);
    
    // データを取得
    int currentRank = UserDataStore::getInstance()->getRank();
    CCLOG("Select - rank:%d", currentRank);
    StringMapVector scoreList = UserDataStore::getInstance()->getScoreTable();
    
    // スコア表示
    float labelWidth = origin.x + visibleSize.width * 1 / 10;
    float relativeLabelHeight;
    Label* resultLabel;
    Point point;
    
    const std::string KEY_RANK = Constant::UserDefaultKey::SCORE_TABLE_RANK();
    const std::string KEY_SCORE = Constant::UserDefaultKey::SCORE_TABLE_SCORE();
    const std::string KEY_BREAK = Constant::UserDefaultKey::SCORE_TABLE_BREAK();
    
    relativeLabelHeight = 8.0f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("次のランク: ", point);
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight -= 1.0f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create(std::to_string(currentRank), point, Constant::LARGE_FONT());
    resultLabel->setScale(BM_FONT_SIZE64(32));
    this->addChild(resultLabel, ZOrder::Font);
    
    relativeLabelHeight = 4.9f;
    point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    resultLabel = TextCreator::create("総合バトルポイント ", point);
    resultLabel->setColor(Color3B(113, 212, 255));
    this->addChild(resultLabel, ZOrder::Font);
    
    for (StringMapVector::iterator it = scoreList.begin(); it != scoreList.end(); it++)
    {
        StringMap map = (*it);
        
        labelWidth = origin.x + visibleSize.width * 2 / 10;
        
        relativeLabelHeight -= .6f;
        point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
        resultLabel = TextCreator::create("HIGH RANK: " + map[KEY_RANK], point);
        this->addChild(resultLabel, ZOrder::Font);
        
        relativeLabelHeight -= .4f;
        point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
        resultLabel = TextCreator::create("TOTAL SCORE: " + map[KEY_SCORE], point);
        this->addChild(resultLabel, ZOrder::Font);
        
        relativeLabelHeight -= .4f;
        point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
        resultLabel = TextCreator::create("TOTAL BREAK: " + map[KEY_BREAK], point);
        this->addChild(resultLabel, ZOrder::Font);
        
        break;
    }
    
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
