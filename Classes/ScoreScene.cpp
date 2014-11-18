#include "ScoreScene.h"
#include "SelectSceneLoader.h"
#include "GoogleAnalyticsTracker.h"
#include "Constant.h"
#include "SoundManager.h"
#include "TextCreator.h"
#include "UserDataStore.h"

ScoreScene::ScoreScene()
{
}

ScoreScene::~ScoreScene()
{
}

bool ScoreScene::init()
{
    GoogleAnalyticsTracker::sendScreen("ScoreScene");
    if(!Layer::init())
    {
        return false;
    }
    
    return true;
}

SEL_MenuHandler ScoreScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    return NULL;
}

Control::Handler ScoreScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBackButton", ScoreScene::tappedBackButton);
    return NULL;
}

void ScoreScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // BGM
    SoundManager* soundManager = new SoundManager();
    soundManager->playBGM("bgm_title", true);
    
    // SE
    soundManager->preloadSE("se_select");
    
    // スコア表示
    float labelWidth = origin.x + visibleSize.width * 1 / 10;
    float relativeLabelHeight;
    Label* resultLabel;
    Point point;
    
    const std::string KEY_RANK = Constant::UserDefaultKey::SCORE_TABLE_RANK();
    const std::string KEY_SCORE = Constant::UserDefaultKey::SCORE_TABLE_SCORE();
    const std::string KEY_BREAK = Constant::UserDefaultKey::SCORE_TABLE_BREAK();
    
    StringMapVector scoreList = UserDataStore::getInstance()->getScoreTable();
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
    }
}

void ScoreScene::tappedBackButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedBackButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    
    Scene* scene = SelectSceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}
