#include "BattleScene.h"
#include "ResultSceneLoader.h"
#include "Constant.h"
#include "GameManager.h"
#include "UserDataStore.h"
#include "CharacterCreator.h"
#include "EnemyCharacter.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include <random>

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

    current_rank = UserDataStore::getRank();

    gameTime = Constant::GAME_TIME;
    this->effectManager = new EffectManager();
    this->effectManager->init();
    this->schedule(schedule_selector(BattleScene::updateBySchedule), 1.0f);
 
    initBackground();
    initEnemy();
    initStatusLayer();
    initTouchEvent();
    
    return true;
}

void BattleScene::initBackground()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    int num = CCRANDOM_0_1() * bgImageList.size();
    Sprite* background = Sprite::createWithSpriteFrameName(StringUtils::format("%s.png", bgImageList.at(num).c_str()));
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
    
    int num = CCRANDOM_0_1() * enemyImageList.size();
    std::string enemyFileName = StringUtils::format("%s.png", enemyImageList.at(num).c_str());

    CharacterCreator* creator = new CharacterCreator();
    enemyData->setImage(creator->create(enemyFileName, CharacterScale::ALL));
    this->addChild(enemyData->getImage(), ZOrder::Enemy);
    }

void BattleScene::initStatusLayer()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // 時間制限
    gameTimeLabel = Label::createWithBMFont("Arial_Black.fnt", StringUtils::toString(gameTime));
    gameTimeLabel->setAnchorPoint(Point(0.5, 0.5));
    gameTimeLabel->setPosition(Point(origin.x + visibleSize.width * 1/ 10,
                                     origin.y + visibleSize.height * 9.5 / 10));
    gameTimeLabel->getTexture()->setAliasTexParameters();
    this->addChild(gameTimeLabel, ZOrder::Font);
    
    // HP
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
    if (enemyData->getHpPercentage() == 0)
    {
        Scene* scene = ResultSceneLoader::createScene();
        TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
        Director::getInstance()->replaceScene(trans);
    }
}

void BattleScene::updateBySchedule( float frame )
{
    gameTime--;
    CCLOG("gameTime:%d", gameTime);
    gameTimeLabel->setString(StringUtils::toString(gameTime));
    
    if (gameTime <= 0)
    {
        Scene* scene = ResultSceneLoader::createScene();
        TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
        Director::getInstance()->replaceScene(trans);
    }
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
    std::vector<std::string>::const_iterator iterator = effectList.begin();
    while (iterator != effectList.end()) {
        soundManager->preloadSE(*iterator);
        CCLOG("preloadSE:%s", (*iterator).c_str());
        iterator++;
    }
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
        int num = CCRANDOM_0_1() * effectList.size();
        soundManager->playSE(effectList.at(num));

        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        
//        Point pos = this->convertTouchToNodeSpace(touch);
//        this->touchEffectMotion->setPosition(pos);

        num = CCRANDOM_0_1() * battleEffectImageList.size();
        Sprite* effectSprite = this->effectManager->effectPurified(battleEffectImageList.at(num), 10, location);
        this->addChild(effectSprite, ZOrder::TouchEffect);
        
        auto preHpPercentage = enemyData->getHpPercentage();
        auto afterHpPercentage =enemyData->getHp() - Constant::BASE_DAMAGE;
        afterHpPercentage = afterHpPercentage < 0 ? 0 : afterHpPercentage;
        enemyData->setHp(afterHpPercentage);
        auto act = ProgressFromTo::create(0.5, preHpPercentage, afterHpPercentage);
        enemyHpBar->runAction(act);
        CCLOG("act:%d / %f%%",enemyData->getHp(), enemyData->getHpPercentage());

        auto damageNumSprite = Label::createWithBMFont("Arial_Black.fnt", StringUtils::toString(Constant::BASE_DAMAGE));
        damageNumSprite->setPosition(effectSprite->getContentSize().width / 2, effectSprite->getContentSize().height / 2);
        damageNumSprite->setAlignment(TextHAlignment::CENTER);
        damageNumSprite->setAnchorPoint(Vec2(-0.5, -1));
        damageNumSprite->setScale(BM_FONT_SIZE64(24));
        effectSprite->addChild(damageNumSprite);
        CCLOG("damageNum:%f, %f", effectSprite->getContentSize().width, effectSprite->getContentSize().height);

        damageNumSprite->runAction(
            Sequence::create(Spawn::create(
                MoveBy::create(1.5f, Vec2(0,50)),
                FadeOut::create(1.5f), NULL),
                CallFuncN::create([&](Node *node){node->removeFromParent();}),
                NULL));

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
