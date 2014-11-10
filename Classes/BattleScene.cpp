#include "BattleScene.h"
#include "ResultSceneLoader.h"
#include "Constant.h"
#include "GameManager.h"
#include "UserDataStore.h"
#include "CharacterCreator.h"
#include "EnemyCharacter.h"
//#include "EnemyTargetter.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "BattleActionCreator.h"
#include <random>

USING_NS_CC;

BattleScene::BattleScene()
: enemyImageList(Constant::ENEMY_IMAGE_LIST())
, bgImageList(Constant::BG_IMAGE_LIST())
, battleEffectImageList(Constant::BATTLE_EFFECT_IMAGE_LIST())
, effectList(Constant::EFFECT_LIST())
, gameTime(Constant::GAME_TIME)
, gameEndFlg(false)
, eternityBreakTime(0)
{
}

BattleScene::~BattleScene()
{
//    CC_SAFE_RELEASE(_topLeft);
//    CC_SAFE_RELEASE(_top);
//    CC_SAFE_RELEASE(_topRight);
//    CC_SAFE_RELEASE(_left);
//    CC_SAFE_RELEASE(_centre);
//    CC_SAFE_RELEASE(_right);
//    CC_SAFE_RELEASE(_bottomLeft);
//    CC_SAFE_RELEASE(_bottom);
//    CC_SAFE_RELEASE(_bottomRight);
//    CC_SAFE_RELEASE(_scale9Image);
}

/**
 初期化
 */
bool BattleScene::init()
{
    CCLOG("init-start");
    if(!CCLayer::init())
    {
        return false;
    }

    CCLOG("init-eternityBreakTime0: %d", eternityBreakTime);
    initBattleResult();
    initBackground();
    initPlayerInfo();
    initEnemy();
    initStatusLayer();
    
    // 数値を初期化
    gameTime = Constant::GAME_TIME;
    gameEndFlg = false;
    eternityBreakTime = 0;
    
    // 開始テキスト表示
    Label* label = Label::createWithSystemFont("START!", "Arial-BoldMT", 40, Size(320, 50), TextHAlignment::CENTER, TextVAlignment::CENTER);
    this->addChild(label, ZOrder::Font);
    
    // 右から現れて左に消える
    static const float labelY = 200;
    static const float marginX = 200;
    label->setPosition(320+marginX, labelY);
    label->runAction(
                     Sequence::create(
                                      MoveTo::create(0.2f, Point(160, labelY)),
                                      DelayTime::create(1.0f),
                                      MoveTo::create(0.2f, Point(-marginX, labelY)),
                                      CallFunc::create([this](){this->setupGame();}), // 開始処理を呼び出し
                                      RemoveSelf::create(),
                                      NULL
                                      )
                     );
    
    CCLOG("init-end");
    return true;
}

void BattleScene::setupGame()
{
    CCLOG("init-eternityBreakTime1: %d", eternityBreakTime);
    this->effectManager = new EffectManager();
    CCLOG("init-eternityBreakTime3: %d", eternityBreakTime);
    this->schedule(schedule_selector(BattleScene::updateBySchedule), 1.0f);
    CCLOG("init-eternityBreakTime4: %d", eternityBreakTime);
    this->scheduleUpdate();
    CCLOG("init-eternityBreakTime5: %d", eternityBreakTime);
    initTouchEvent();

    // BGM
    SoundManager* soundManager = new SoundManager();
    CCLOG("onNodeLoaded-new SoundManager");
    soundManager->playBGM("bgm_battle", true);
    CCLOG("onNodeLoaded-playBGM");
    
    // SE
    std::vector<std::string>::const_iterator iterator = effectList.begin();
    CCLOG("onNodeLoaded-iterator");
    while (iterator != effectList.end()) {
        soundManager->preloadSE(*iterator);
        CCLOG("preloadSE:%s", (*iterator).c_str());
        iterator++;
    }
}

/**
 バトルリザルト数値を初期化
 */
void BattleScene::initBattleResult()
{
    GameManager::getInstance()->battleDamagePoint = 0;
    GameManager::getInstance()->battleEternityPoint = 0;
    
    currentRank = UserDataStore::getInstance()->getRank();
}

/**
 背景を初期化
 */
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

/**
 プレイヤー情報を初期化
 */
void BattleScene::initPlayerInfo()
{
    playerInfo = PlayerBattleInfo::create();
    playerInfo->retain();
    playerInfo->setEp(0);
}

/**
 敵キャラクターを初期化
 */
void BattleScene::initEnemy()
{
    enemyData = EnemyCharacter::create();
    enemyData->retain();
    enemyData->setMaxHp(Constant::DEFAULT_ENEMY_HP + currentRank * Constant::HP_RANK_UP_INCREMENT);
    enemyData->setHp(enemyData->getMaxHp());
    CCLOG("HP: %d / %d", enemyData->getMaxHp(), enemyData->getHp());
    
    int num = CCRANDOM_0_1() * enemyImageList.size();
    std::string enemyFileName = StringUtils::format("%s.png", enemyImageList.at(num).c_str());

    CharacterCreator* creator = new CharacterCreator();
    creator->init(CharacterScale::ALL);
    enemyData->setImage(creator->create(enemyFileName));

    nodeGrid = NodeGrid::create();
    nodeGrid->addChild(enemyData->getImage());
    this->addChild(nodeGrid, ZOrder::Enemy);
}

/**
 ステータスレイヤーを初期化
 */
void BattleScene::initStatusLayer()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // ランク
    Label* rankLabel = Label::createWithBMFont(Constant::NORMAL_FONT(), StringUtils::toString(currentRank));
    rankLabel->setAnchorPoint(Point(0.5, 0.5));
    rankLabel->setPosition(Point(origin.x + visibleSize.width * 1 / 10,
                                 origin.y + visibleSize.height * 9.5 / 10));
    rankLabel->getTexture()->setAliasTexParameters();
    this->addChild(rankLabel, ZOrder::Font);
    
    // 時間制限
    gameTimeLabel = Label::createWithBMFont(Constant::NORMAL_FONT(), StringUtils::toString(gameTime));
    gameTimeLabel->setAnchorPoint(Point(0.5, 0.5));
    gameTimeLabel->setPosition(Point(origin.x + visibleSize.width * 9 / 10,
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

    // EP
    Sprite* epFrame = Sprite::createWithSpriteFrameName("ep_frame.png");
    epFrame->setPosition(Point(origin.x + visibleSize.width / 2,
                               origin.y + visibleSize.height * 0.5 / 10));
    addChild(epFrame, ZOrder::PlayerEp);
    
    Sprite* ep = Sprite::createWithSpriteFrameName("ep.png");
    playerEpBar = ProgressTimer::create(ep);
    playerEpBar->setPosition(Point(epFrame->getContentSize().width / 2, epFrame->getContentSize().height / 2));
    playerEpBar->setType(ProgressTimer::Type::BAR);
    playerEpBar->setMidpoint(Point::ZERO);
    playerEpBar->setBarChangeRate(Point(1, 0));
    playerEpBar->setPercentage(playerInfo->getEpPercentage());
    epFrame->addChild(playerEpBar);
}

/**
 タッチイベントを初期化
 */
void BattleScene::initTouchEvent()
{
    touchOn();
    
    // タッチエフェクト
//    Sprite* effect = Sprite::createWithSpriteFrameName("touchEffect.png");
//    touchEffectMotion = MotionStreak::create(1.0, 0.5f, 40.0f, Color3B(87,174,155), effect->getTexture());
//    addChild(touchEffectMotion, ZOrder::TouchEffect);
}

/**
 *  定期更新（1秒毎）
 *
 *  @param frame フレーム
 */
void BattleScene::updateBySchedule(float frame)
{
    CCLOG("updateBySchedule-start");
    if (gameTime <= 0)
    {
        endBattle();
        return;
    }
    
    gameTime--;
    CCLOG("updateBySchedule-gameTime:%d", gameTime);
    CCLOG("updateBySchedule-eternityBreakTime: %d", eternityBreakTime);
    if (eternityBreakTime > 0)
    {
        eternityBreakTime--;
    }
    
    gameTimeLabel->setString(StringUtils::toString(gameTime));
    if (eternityBreakTime > 0)
    {
        gameTimeLabel->setColor(Color3B::MAGENTA);
    }
    else
    {
        gameTimeLabel->setColor(Color3B(255,255,255));
    }
    
//    if (gameTime == 10)
//    {
//        Size visibleSize = Director::getInstance()->getVisibleSize();
//        Point origin = Director::getInstance()->getVisibleOrigin();
//        
//        EnemyTargetter* enemyTargetter = EnemyTargetter::create();
//        targetter->retain();
//        std::string fileName = "touchEffect.png";
//        CharacterCreator* creator = new CharacterCreator();
//        targetter->setImage(creator->create(fileName, CharacterScale::ALL));
//        
//        Point point = Point(origin.x + visibleSize.width * 1/ 10,
//                            origin.y + visibleSize.height * 9.5 / 10);
//        targetter->setPosition(point);
//        Node* targetGrid = NodeGrid::create();
//        targetGrid->addChild(enemyData->getImage(), ZOrder::EnemyTargetter);
//    }
    CCLOG("updateBySchedule-end");
}

/**
 *  定期更新（フレーム毎）
 *
 *  @param frame フレーム
 */
void BattleScene::update(float frame)
{
//    CCLOG("update-start");
    
    // EPブレイク
    if (playerInfo->getEp() == Constant::MAX_PLAYER_EP)
    {
        CCLOG("update-ep-break EP: %d", playerInfo->getEp());
        CCLOG("update-ep-break eternityBreakTime: %d", eternityBreakTime);
        playerInfo->incrementBattleEpCount();
        playerInfo->setEp(0);
        eternityBreakTime = Constant::ETERNITY_BREAK_TIME;
        CCLOG("update-ep-break EP: %d", playerInfo->getEp());
        CCLOG("update-ep-break eternityBreakTime: %d", eternityBreakTime);
    }
    
    
    // 敵撃破
    if (!gameEndFlg && enemyData->getHp() == 0)
    {
        touchOff();
        gameEndFlg = true;
        nodeGrid->runAction(BattleActionCreator::defeatEnemy());
        this->scheduleOnce(schedule_selector(BattleScene::updateByDefeatEnemy), 5.0f);
    }
//    CCLOG("update-end");
}

/**
 *  敵撃破時に行う処理
 *
 *  @param frame フレーム
 */
void BattleScene::updateByDefeatEnemy(float frame)
{
    endBattle();
}

/**
 *  CocosBuilderで作成したメニューアイテム選択時処理
 *
 *  @param pTarget       pTarget
 *  @param pSelectorName pSelectorName
 *
 *  @return NULL
 */
SEL_MenuHandler BattleScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);

    return NULL;
}

/**
 *  CocosBuilderで作成したコントロール選択時処理
 *
 *  @param pTarget       pTarget
 *  @param pSelectorName pSelectorName
 *
 *  @return NULL
 */
Control::Handler BattleScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedResultButton", BattleScene::tappedResultButton);
    return NULL;
}

/**
 *  Nodeロード時処理
 *
 *  @param pNode       pNode
 *  @param pNodeLoader pNodeLoader
 */
void BattleScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    CCLOG("onNodeLoaded");
}

/**
 *  Resultボタンタップ時処理
 *
 *  @param pTarget           pTarget
 *  @param pControlEventType pControlEventType
 */
void BattleScene::tappedResultButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedResultButton eventType = %d", pControlEventType);
    endBattle();
}

/**
 *  バトル終了処理
 */
void BattleScene::endBattle()
{
    this->unschedule(schedule_selector(BattleScene::updateBySchedule));
    GameManager::getInstance()->battleDamagePoint = enemyData->getMaxHp() - enemyData->getHp();
    GameManager::getInstance()->battleEternityPoint = playerInfo->getbattleEpCount();

    replaceScene();
}

/**
 *  画面遷移処理
 */
void BattleScene::replaceScene()
{
    Scene* scene = ResultSceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}

/**
 *  タッチイベント有効化
 */
void BattleScene::touchOn()
{
//    listener = EventListenerTouchAllAtOnce::create();
//    listener->onTouchesBegan = CC_CALLBACK_2(BattleScene::onTouchesBegan, this);
//    listener->onTouchesMoved = CC_CALLBACK_2(BattleScene::onTouchesMoved, this);
//    listener->onTouchesEnded = CC_CALLBACK_2(BattleScene::onTouchesEnded, this);
//    listener->onTouchesCancelled = CC_CALLBACK_2(BattleScene::onTouchesCancelled, this);

    CCLOG("touchOn-start");
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(BattleScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(BattleScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(BattleScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(BattleScene::onTouchCancelled, this);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    CCLOG("touchOn-end");
}

/**
 *  タッチイベント無効化
 */
void BattleScene::touchOff()
{
	this->getEventDispatcher()->removeEventListener(listener);
}

/**
 *  タッチ開始処理
 *
 *  @param touch   touch
 *  @param event   event
 */
bool BattleScene::onTouchBegan(Touch* touch, Event *event){
    SoundManager* soundManager = new SoundManager();

    // ゲームエンドの場合は処理しない
    if (gameEndFlg) return true;

    // タッチ位置
    auto location = touch->getLocation();

    int damage;             // 与えたダメージ
    int soundEffectNum;     // 効果音
    int hitSpriteNum;       // ヒットエフェクト
    CCLOG("onTouchBegan-eternityBreakTime: %d", eternityBreakTime);
    CCLOG("onTouchBegan-gameEndFlg: %d", gameEndFlg);
    if (eternityBreakTime == 0)
    {
        // 通常時
        damage = Constant::BASE_DAMAGE + CCRANDOM_0_1() * Constant::DAMAGE_RANK_UP_INCREMENT;
        soundEffectNum = CCRANDOM_0_1() * 2;
        hitSpriteNum = CCRANDOM_0_1() * 2;
    }
    else
    {
        // Eブレイク時
        damage = Constant::BASE_DAMAGE_BREAK + CCRANDOM_0_1() * Constant::DAMAGE_RANK_UP_INCREMENT;
        soundEffectNum = CCRANDOM_0_1() * (effectList.size() - 2) + 2;
        hitSpriteNum = CCRANDOM_0_1() * (battleEffectImageList.size() - 2) + 2;
    }

    
    // 効果音
    soundManager->playSE(effectList.at(soundEffectNum));
    
    // ヒットエフェクト生成
    Sprite* effectSprite = this->effectManager->effectPurified(battleEffectImageList.at(hitSpriteNum), 10, location);
    this->addChild(effectSprite, ZOrder::TouchEffect);
    
    // 敵のHPゲージ
    auto preHpPercentage = enemyData->getHpPercentage();
    auto afterHp = enemyData->getHp() - damage;
    afterHp = afterHp < 0 ? 0 : afterHp;
    enemyData->setHp(afterHp);
    auto enemyAct = ProgressFromTo::create(0.5, preHpPercentage, enemyData->getHpPercentage());
    enemyHpBar->runAction(enemyAct);
    CCLOG("onTouchBegan-enemyHp:%d / %f%%",enemyData->getHp(), enemyData->getHpPercentage());
    
    // プレイヤーEPゲージ
    auto preEpPercentage = playerInfo->getEpPercentage();
    auto afterEp = playerInfo->getEp() + Constant::EP_INCREMENT;
    afterEp = afterEp > Constant::MAX_PLAYER_EP ? Constant::MAX_PLAYER_EP : afterEp;
    playerInfo->setEp(afterEp);
    auto playerAct = ProgressFromTo::create(0.5, preEpPercentage, playerInfo->getEpPercentage());
    playerEpBar->runAction(playerAct);
    CCLOG("onTouchBegan-playerEp:%d / %f%%",playerInfo->getEp(), playerInfo->getEpPercentage());
    
    // ダメージ値生成
    auto damageNumSprite = Label::createWithBMFont(Constant::NORMAL_FONT(), StringUtils::toString(damage));
    damageNumSprite->setPosition(effectSprite->getContentSize().width / 2, effectSprite->getContentSize().height / 2);
    damageNumSprite->setAlignment(TextHAlignment::CENTER);
    damageNumSprite->setAnchorPoint(Vec2(-0.5, -1));
    damageNumSprite->setScale(BM_FONT_SIZE64(24));
    if (eternityBreakTime > 0) damageNumSprite->setColor(Color3B::MAGENTA);
//    damageNumSprite->updateDisplayedColor(Color3B(100,200,255));
    effectSprite->addChild(damageNumSprite);
    
    // 敵のダメージエフェクト生成
    damageNumSprite->runAction(BattleActionCreator::attackToEnemy());
    nodeGrid->runAction(BattleActionCreator::damageToEnemy3());
    nodeGrid->setGrid(NULL);
    
//    CCLOG("(onTouchesBegan) x:%f, y:%f", location.x, location.y);
    return true;
}

/**
 *  タッチ移動時処理
 *
 *  @param touch   touch
 *  @param event   event
 */
void BattleScene::onTouchMoved(Touch* touch, Event *event){
    
    // ゲームエンドの場合は処理しない
    if (gameEndFlg) return;
    
    auto location = touch->getLocation();
    
    //        Point pos = this->convertTouchToNodeSpace(touch);
    //        this->touchEffectMotion->setPosition(pos);
    
//    CCLOG("(onTouchesMoved) x:%f, y:%f", location.x, location.y);
    
    return;
}

/**
 *  タッチ終了時処理
 *
 *  @param touch   touch
 *  @param event   event
 */
void BattleScene::onTouchEnded(Touch* touch, Event *event){
    
    // ゲームエンドの場合は処理しない
    if (gameEndFlg) return;
    
    auto location = touch->getLocation();
    
//    CCLOG("(onTouchesEnded) x:%f, y:%f", location.x, location.y);

    return;
}

/**
 *  タッチキャンセル時処理
 *
 *  @param touch   touch
 *  @param event   event
 */
void BattleScene::onTouchCancelled(Touch* touch, Event *event){

    // ゲームエンドの場合は処理しない
    if (gameEndFlg) return;
    
    auto location = touch->getLocation();

//    CCLOG("(onTouchesEnded) x:%f, y:%f", location.x, location.y);

    return;
}

// ↓マルチタッチ用
///**
// *  タッチ開始処理
// *
// *  @param touches touches
// *  @param event   event
// */
//void BattleScene::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
//    SoundManager* soundManager = new SoundManager();
//    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
//    while (iterator != touches.end()) {
//
//        // タッチ位置
//        Touch* touch = (Touch*)(*iterator);
//        auto location = touch->getLocation();
//        
//        // 与えたダメージ
//        int damage = Constant::BASE_DAMAGE + CCRANDOM_0_1() * Constant::DAMAGE_RANK_UP_INCREMENT;
//
//        // 効果音
//        int num = CCRANDOM_0_1() * effectList.size();
//        soundManager->playSE(effectList.at(num));
//
//        // ヒットエフェクト生成
//        num = CCRANDOM_0_1() * battleEffectImageList.size();
//        Sprite* effectSprite = this->effectManager->effectPurified(battleEffectImageList.at(num), 10, location);
//        this->addChild(effectSprite, ZOrder::TouchEffect);
//        
//        // 敵のHPゲージ
//        auto preHpPercentage = enemyData->getHpPercentage();
//        auto afterHp = enemyData->getHp() - damage;
//        afterHp = afterHp < 0 ? 0 : afterHp;
//        enemyData->setHp(afterHp);
//        auto act = ProgressFromTo::create(0.5, preHpPercentage, enemyData->getHpPercentage());
//        enemyHpBar->runAction(act);
//        CCLOG("act:%d / %f%%",enemyData->getHp(), enemyData->getHpPercentage());
//
//        // ダメージエフェクト生成
//        auto damageNumSprite = Label::createWithBMFont(Constant::NORMAL_FONT(), StringUtils::toString(damage));
//        damageNumSprite->setPosition(effectSprite->getContentSize().width / 2, effectSprite->getContentSize().height / 2);
//        damageNumSprite->setAlignment(TextHAlignment::CENTER);
//        damageNumSprite->setAnchorPoint(Vec2(-0.5, -1));
//        damageNumSprite->setScale(BM_FONT_SIZE64(24));
//        effectSprite->addChild(damageNumSprite);
//
//        damageNumSprite->runAction(BattleActionCreator::attackToEnemy());
//        nodeGrid->runAction(BattleActionCreator::damageToEnemy2());
//
//        iterator++;
//        CCLOG("(onTouchesBegan) x:%f, y:%f", location.x, location.y);
//    }
//    return;
//}
//
///**
// *  タッチ移動時処理
// *
// *  @param touches touches
// *  @param event   event
// */
//void BattleScene::onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
//    
//    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
//    while (iterator != touches.end()) {
//        Touch* touch = (Touch*)(*iterator);
//        auto location = touch->getLocation();
//
////        Point pos = this->convertTouchToNodeSpace(touch);
////        this->touchEffectMotion->setPosition(pos);
//        
//        iterator++;
//        CCLOG("(onTouchesMoved) x:%f, y:%f", location.x, location.y);
//    }
//    
//    return;
//}
//
///**
// *  タッチ終了時処理
// *
// *  @param touches touches
// *  @param event   event
// */
//void BattleScene::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
//    
//    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
//    while (iterator != touches.end()) {
//        Touch* touch = (Touch*)(*iterator);
//        auto location = touch->getLocation();
//        
//        iterator++;
//        CCLOG("(onTouchesEnded) x:%f, y:%f", location.x, location.y);
//    }
//    return;
//}
//
///**
// *  タッチキャンセル時処理
// *
// *  @param touches touches
// *  @param event   event
// */
////void BattleScene::onTouchesCancelled(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
////    
////    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
////    while (iterator != touches.end()) {
////        Touch* touch = (Touch*)(*iterator);
////        auto location = touch->getLocation();
////        
////        iterator++;
////        CCLOG("(onTouchesEnded) x:%f, y:%f", location.x, location.y);
////    }
////    return;
////}
