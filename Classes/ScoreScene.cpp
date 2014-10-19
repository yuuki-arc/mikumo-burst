#include "ScoreScene.h"
#include "SelectSceneLoader.h"
#include "Constant.h"
#include "SoundManager.h"
#include "UserDataStore.h"

ScoreScene::ScoreScene()
{
}

ScoreScene::~ScoreScene()
{
}

bool ScoreScene::init()
{
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
    
    // 結果
    auto label = Label::createWithBMFont("Arial_Black.fnt", "SCORE");
    label->setAnchorPoint(Point(0, 0.5));
    label->setPosition(Point(origin.x + visibleSize.width * 1/ 10,
                             origin.y + visibleSize.height * 9.5 / 10));
    label->setColor(Color3B(113, 212, 255));
    label->getTexture()->setAliasTexParameters();
    this->addChild(label, ZOrder::Font);
    
    StringMapVector scoreList = UserDataStore::getHighScore();
    int count = 0;
    for (StringMapVector::iterator it = scoreList.begin(); it != scoreList.end(); it++)
    {
        StringMap map = (*it);
        Label* reultLabel = Label::createWithBMFont("Arial_Black.fnt", "CHAIN: " + map["chain"]);
        reultLabel->setAnchorPoint(Point(0, 0.5));
        reultLabel->setScale(BM_FONT_SIZE64(16));
        reultLabel->setPosition(Point(origin.x + visibleSize.width * 1/ 10,
                                      origin.y + visibleSize.height * (8.5 - count) / 10));
        reultLabel->getTexture()->setAliasTexParameters();
        this->addChild(reultLabel, ZOrder::Font);
        
        reultLabel = Label::createWithBMFont("Arial_Black.fnt", "SCORE: " + map["score"]);
        reultLabel->setAnchorPoint(Point(0, 0.5));
        reultLabel->setScale(BM_FONT_SIZE64(16));
        reultLabel->setPosition(Point(origin.x + visibleSize.width * 1/ 10,
                                      origin.y + visibleSize.height * (8.0 - count) / 10));
        reultLabel->getTexture()->setAliasTexParameters();
        this->addChild(reultLabel, ZOrder::Font);
        
        count++;
    }
    
    //    Label* reultLabel = Label::createWithBMFont("Arial_Black.fnt", UserDataStore::getHighScore());
    //    reultLabel->setAnchorPoint(Point(0.5, 0.5));
    //    reultLabel->setPosition(Point(origin.x + visibleSize.width * 1/ 10,
    //                                  origin.y + visibleSize.height * 9.5 / 10));
    //    reultLabel->getTexture()->setAliasTexParameters();
    //    this->addChild(reultLabel, ZOrder::Font);
    
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
