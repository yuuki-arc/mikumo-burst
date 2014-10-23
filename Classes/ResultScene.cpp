#include "ResultScene.h"
#include "SelectSceneLoader.h"
#include "Constant.h"
#include "GameManager.h"
#include "SoundManager.h"
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
    int score = GameManager::getInstance()->battleDamagePoint;
    int ebCount = GameManager::getInstance()->battleEternityPoint;
    
    // 結果
    auto label = Label::createWithBMFont("Arial_Black.fnt", "RESULT");
    label->setAnchorPoint(Point(0, 0.5));
    label->setPosition(Point(origin.x + visibleSize.width * 1/ 10,
                             origin.y + visibleSize.height * 9.5 / 10));
    label->setColor(Color3B(113, 212, 255));
    label->getTexture()->setAliasTexParameters();
    this->addChild(label, ZOrder::Font);

    // スコア表示
    Label* reultLabel = Label::createWithBMFont("Arial_Black.fnt", "SCORE: " + std::to_string(score));
    reultLabel->setAnchorPoint(Point(0, 0.5));
    reultLabel->setScale(BM_FONT_SIZE64(16));
    reultLabel->setPosition(Point(origin.x + visibleSize.width * 1/ 10,
                                  origin.y + visibleSize.height * 8.5 / 10));
    reultLabel->getTexture()->setAliasTexParameters();
    this->addChild(reultLabel, ZOrder::Font);
    
    reultLabel = Label::createWithBMFont("Arial_Black.fnt", "BREAK: " + std::to_string(ebCount));
    reultLabel->setAnchorPoint(Point(0, 0.5));
    reultLabel->setScale(BM_FONT_SIZE64(16));
    reultLabel->setPosition(Point(origin.x + visibleSize.width * 1/ 10,
                                  origin.y + visibleSize.height * 8.0 / 10));
    reultLabel->getTexture()->setAliasTexParameters();
    this->addChild(reultLabel, ZOrder::Font);

    // スコア保存
    StringMapVector scoreList = UserDataStore::getHighScore();
    StringMap scoreMap;
    scoreMap.insert(std::make_pair("score", std::to_string(score)));
    scoreMap.insert(std::make_pair("break", std::to_string(ebCount)));
    scoreList.push_back(scoreMap);
    UserDataStore::setHighScore(scoreList);

//    Label* reultLabel = Label::createWithBMFont("Arial_Black.fnt", UserDataStore::getHighScore());
//    reultLabel->setAnchorPoint(Point(0.5, 0.5));
//    reultLabel->setPosition(Point(origin.x + visibleSize.width * 1/ 10,
//                                  origin.y + visibleSize.height * 9.5 / 10));
//    reultLabel->getTexture()->setAliasTexParameters();
//    this->addChild(reultLabel, ZOrder::Font);
    
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
