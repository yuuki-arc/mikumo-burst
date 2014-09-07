#include "BattleScene.h"
#include "ResultSceneLoader.h"
#include "Constant.h"
#include "GameManager.h"
#include "CharacterCreator.h"
#include "EnemyCharacter.h"
#include "EffectManager.h"
#include "SoundManager.h"

USING_NS_CC;

BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}

bool BattleScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }

    current_rank = userDefault->getIntegerForKey(Constant::UserDefaultKey::RANK(), 1);

    initBackground();
    initEnemy();
    initStatusLayer();
    initTouchEvent();
    
    gameTime = 0;
    this->schedule(schedule_selector(BattleScene::updateBySchedule), 1.0f);
    
    return true;
}

void BattleScene::initBackground()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* background = Sprite::create("bg/001-1.png");
    background->setPosition(Point(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2));
    
    if (GameManager::getInstance()->isScreenModeHd())
    {
        background->setScale(background->getScale()*1.6, background->getScale()*1.6);
    }
    else
    {
        background->setScale(background->getScale()*0.8, background->getScale()*0.8);
    }
    this->addChild(background, ZOrder::Bg);
}

void BattleScene::initEnemy()
{
    enemyData = EnemyCharacter::create();
    enemyData->retain();
    enemyData->setMaxHp(Constant::DEFAULT_ENEMY_HP + current_rank * 100000);
    enemyData->setHp(enemyData->getMaxHp());
    CCLOG("HP: %d / %d", enemyData->getMaxHp(), enemyData->getHp());
    
    CharacterCreator* creator = new CharacterCreator();
    enemyData->setImage(creator->create("f271.png", CharacterScale::ALL));
    this->addChild(enemyData->getImage(), ZOrder::Enemy);
    }

void BattleScene::initStatusLayer()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* hpFrame = Sprite::createWithSpriteFrameName("hp_frame.png");
    hpFrame->setPosition(Point(origin.x + visibleSize.width / 2,
                               origin.y + visibleSize.height * 9.5 / 10));
    addChild(hpFrame, ZOrder::EnemyHp);
    
    Sprite* hp = Sprite::createWithSpriteFrameName("hp.png");
    enemyHpBar = ProgressTimer::create(hp);
    enemyHpBar->setPosition(Point(hpFrame->getContentSize().width / 2, hpFrame->getContentSize().height / 2));
    enemyHpBar->setType(ProgressTimer::Type::BAR);
    enemyHpBar->setMidpoint(Point::ZERO);
    enemyHpBar->setBarChangeRate(Point(1, 0));
    enemyHpBar->setPercentage(enemyData->getHpPercentage());
    hpFrame->addChild(enemyHpBar);
}

void BattleScene::initTouchEvent()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    //    listener->setSwallowTouches(true);
    listener->onTouchesBegan = CC_CALLBACK_2(BattleScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(BattleScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(BattleScene::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    // タッチエフェクト
//    Sprite* effect = Sprite::createWithSpriteFrameName("touchEffect.png");
//    touchEffectMotion = MotionStreak::create(1.0, 0.5f, 40.0f, Color3B(87,174,155), effect->getTexture());
//    addChild(touchEffectMotion, ZOrder::TouchEffect);
}

void BattleScene::update( float frame )
{
//    CCLOG("フレーム単位で呼び出される");
}

void BattleScene::updateBySchedule( float frame )
{
    gameTime++;
}

SEL_MenuHandler BattleScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);

    return NULL;
}

Control::Handler BattleScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedResultButton", BattleScene::tappedResultButton);
    return NULL;
}

void BattleScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    // BGM
    SoundManager* soundManager = new SoundManager();
    soundManager->playBGM("bgm_battle", true);

    // SE
    soundManager->preloadSE("se_battle_blow");
    soundManager->preloadSE("se_battle_darkness");
    soundManager->preloadSE("se_battle_fire");
    soundManager->preloadSE("se_battle_gun");
    soundManager->preloadSE("se_battle_water");
}

void BattleScene::tappedResultButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedResultButton eventType = %d", pControlEventType);
    Scene* scene = ResultSceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}

void BattleScene::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
    SoundManager* soundManager = new SoundManager();
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
//        soundManager->preloadSE("se_battle_blow");
//        soundManager->preloadSE("se_battle_darkness");
        soundManager->playSE("se_battle_fire");
//        soundManager->preloadSE("se_battle_gun");
//        soundManager->preloadSE("se_battle_water");

        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        
//        Point pos = this->convertTouchToNodeSpace(touch);
//        this->touchEffectMotion->setPosition(pos);
        
        this->effectManager = new EffectManager();
        Sprite* sprite = this->effectManager->effectPurified("attackTarget", 10, location);
        this->addChild(sprite, ZOrder::TouchEffect);
        
        auto preHpPercentage = enemyData->getHpPercentage();
        enemyData->setHp(enemyData->getHp() - 1000);
        auto act = ProgressFromTo::create(0.5, preHpPercentage, enemyData->getHpPercentage());
        enemyHpBar->runAction(act);
        CCLOG("act:%d / %f%%",enemyData->getHp(), enemyData->getHpPercentage());


        iterator++;
        CCLOG("(onTouchesBegan) x:%f, y:%f", location.x, location.y);
    }
    return;
}
void BattleScene::onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
    
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();

//        Point pos = this->convertTouchToNodeSpace(touch);
//        this->touchEffectMotion->setPosition(pos);
        
        iterator++;
        CCLOG("(onTouchesMoved) x:%f, y:%f", location.x, location.y);
    }
    
    return;
}
void BattleScene::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
    
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        
        iterator++;
        CCLOG("(onTouchesEnded) x:%f, y:%f", location.x, location.y);
    }
    return;
}
