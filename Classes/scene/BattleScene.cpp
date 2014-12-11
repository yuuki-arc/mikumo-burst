#include "scene/BattleScene.h"
#include "scene/ResultSceneLoader.h"
#include "tools/GoogleAnalyticsTracker.h"
#include "core/Constant.h"
#include "core/GameManager.h"
#include "resources/UserDataStore.h"
#include "factory/CharacterCreator.h"
#include "actor/EnemyCharacter.h"
#include "actor/EnemyNormalCharacter.h"
#include "actor/EnemyBossCharacter.h"
//#include "actor/EnemyTargetter.h"
#include "resources/EffectManager.h"
#include "resources/SoundManager.h"
#include "factory/TextCreator.h"
#include "factory/BattleActionCreator.h"
#include <random>

USING_NS_CC;

BattleScene::BattleScene()
: bgImageList(Constant::BG_IMAGE_LIST())
, gameTime(Constant::GAME_TIME)
, upGameTime(0)
, gameEndFlg(false)
, burstTime(0)
, burstCutInFlg(false)
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
    GoogleAnalyticsTracker::sendScreen("BattleScene");
    if(!CCLayer::init())
    {
        return false;
    }

    initBattleResult();
    initBackground();
    initPlayerInfo();
    initEnemy();
    initStatusLayer();
    
    // 数値を初期化
    gameTime = Constant::GAME_TIME;
    upGameTime = 0;
    gameEndFlg = false;
    burstTime = 0;
    burstCutInFlg = false;
    
    // BGM
    SoundManager* soundManager = new SoundManager();
    if (GameManager::getInstance()->isBattleModeNormal())
    {
        soundManager->playBGM("bgm_battle", true);
    }
    else
    {
        soundManager->playBGM("bgm_battle_boss", true);
    }
    
    // SE
    for (auto& kv : Constant::EFFECT_LIST()) {
        Constant::StringVector effectList = (Constant::StringVector)(kv.second);
        Constant::StringVector::const_iterator iterator = effectList.begin();
        while (iterator != effectList.end()) {
            soundManager->preloadSE(*iterator);
            CCLOG("preloadSE:%s", (*iterator).c_str());
            iterator++;
        }
    }

    // 開始テキスト表示
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    Label* label = TextCreator::create("BATTLE START!", Point(0,0));
    label->setAnchorPoint(Point(0.5, 0.5));
    label->setScale(BM_FONT_SIZE64(32));
    label->getTexture()->setAliasTexParameters();
    this->addChild(label, ZOrder::Font);
    
    // ゲーム開始アニメーション
    float marginX = label->getContentSize().width * 2;
    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2;
    label->setPosition(Point(x+marginX,y));
    label->runAction(
                     Sequence::create(
                                      DelayTime::create(1.0f),
                                      MoveTo::create(0.5f, Point(x, y)),
                                      DelayTime::create(1.0f),
                                      MoveTo::create(0.5f, Point(-marginX, y)),
                                      CallFunc::create([this](){this->setupGame();}), // 開始処理を呼び出し
                                      RemoveSelf::create(),
                                      nullptr
                                      )
                     );
    
    CCLOG("init-end");
    return true;
}

void BattleScene::setupGame()
{
    this->effectManager = new EffectManager();
    this->schedule(schedule_selector(BattleScene::updateBySchedule), 1.0f);
    this->scheduleUpdate();
    initTouchEvent();
}

/**
 バトルリザルト数値を初期化
 */
void BattleScene::initBattleResult()
{
    GameManager::getInstance()->battleDamagePoint = 0;
    GameManager::getInstance()->tapCount = 0;
    GameManager::getInstance()->burstCount = 0;
}

/**
 背景を初期化
 */
void BattleScene::initBackground()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    int num = arc4random() % bgImageList.size();
    Sprite* background = Sprite::createWithSpriteFrameName(StringUtils::format("%s.png", bgImageList.at(num).c_str()));
    background->setPosition(Point(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2));
    
    float scale = Director::getInstance()->getContentScaleFactor();
    background->setScale(background->getScale()*scale, background->getScale()*scale);
    
    this->addChild(background, ZOrder::Bg);
}

/**
 プレイヤー情報を初期化
 */
void BattleScene::initPlayerInfo()
{
    playerInfo = PlayerBattleInfo::create(GameManager::getInstance()->getCharaSelect());
    playerInfo->retain();
    playerInfo->setRank(GameManager::getInstance()->getBattleRank());
    playerInfo->setBp(0);
    this->addChild(playerInfo->getIconImage(), ZOrder::PlayerBp);

    playerInfo->getCutInImage1()->setVisible(false);
    this->addChild(playerInfo->getCutInImage1(), ZOrder::PlayerCutIn);
    playerInfo->getCutInImage2()->setVisible(false);
    this->addChild(playerInfo->getCutInImage2(), ZOrder::PlayerCutIn);
    playerInfo->getCutInImage3()->setVisible(false);
    this->addChild(playerInfo->getCutInImage3(), ZOrder::PlayerCutIn);
}

/**
 敵キャラクターを初期化
 */
void BattleScene::initEnemy()
{
    if (GameManager::getInstance()->isBattleModeNormal())
    {
        enemyData = EnemyNormalCharacter::create();
    }
    else
    {
        enemyData = EnemyBossCharacter::create();
    }
    enemyData->retain();
    
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
    
    // 時間制限
    Point point;
    point = Point(origin.x + visibleSize.width * 9 / 10,
                  origin.y + visibleSize.height * 9 / 10);
    gameTimeLabel = TextCreator::create(StringUtils::toString(gameTime), point);
    gameTimeLabel->setAnchorPoint(Point(0.5, 0.5));
    gameTimeLabel->setScale(BM_FONT_SIZE64(32));
    gameTimeLabel->getTexture()->setAliasTexParameters();
    this->addChild(gameTimeLabel, ZOrder::Font);
    
    // HP
    Sprite* hpFrame = Sprite::createWithSpriteFrameName("hp_frame.png");
    hpFrame->setPosition(Point(origin.x + visibleSize.width / 2,
                               origin.y + visibleSize.height * 9 / 10));
    addChild(hpFrame, ZOrder::EnemyHp);
    
    Sprite* hp = Sprite::createWithSpriteFrameName("hp.png");
    enemyHpBar = ProgressTimer::create(hp);
    enemyHpBar->setPosition(Point(hpFrame->getContentSize().width / 2, hpFrame->getContentSize().height / 2));
    enemyHpBar->setType(ProgressTimer::Type::BAR);
    enemyHpBar->setMidpoint(Point::ZERO);
    enemyHpBar->setBarChangeRate(Point(1, 0));
    enemyHpBar->setPercentage(enemyData->getHpPercentage());
    hpFrame->addChild(enemyHpBar);

//    // ランク
//    std::string battleRank = std::to_string(GameManager::getInstance()->getBattleRank());
//    point = Point(origin.x + visibleSize.width * 1.5 / 10,
//                  origin.y + visibleSize.height * 0.5 / 10);
//    Label* rankLabel = TextCreator::create(battleRank, point);
//    rankLabel->setAnchorPoint(Point(0.5, 0.5));
//    rankLabel->getTexture()->setAliasTexParameters();
//    this->addChild(rankLabel, ZOrder::Font);
    
    // BP
    Sprite* bpFrame = Sprite::createWithSpriteFrameName("ep_frame.png");
    bpFrame->setPosition(Point(origin.x + visibleSize.width * 6 / 10,
                               origin.y + visibleSize.height * 1 / 10));
    addChild(bpFrame, ZOrder::PlayerBp);
    
    Sprite* bp = Sprite::createWithSpriteFrameName("ep.png");
    playerBpBar = ProgressTimer::create(bp);
    playerBpBar->setPosition(Point(bpFrame->getContentSize().width / 2, bpFrame->getContentSize().height / 2));
    playerBpBar->setType(ProgressTimer::Type::BAR);
    playerBpBar->setMidpoint(Point::ZERO);
    playerBpBar->setBarChangeRate(Point(1, 0));
    playerBpBar->setPercentage(playerInfo->getBpPercentage());
    bpFrame->addChild(playerBpBar);
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
    // ゲームエンドおよびカットインアニメーション時は処理しない
    if (gameEndFlg || burstCutInFlg) return;

    if (gameTime <= 0)
    {
        Constant::StringVector list = Constant::VOICE_LIST(GameManager::getInstance()->getCharaSelect(),
                                                           Constant::Voice::BattleEnd);
        int num = arc4random() % list.size();
        SoundManager* soundManager = new SoundManager();
        soundManager->playVoice(list[num]);
        
        endBattle();
        return;
    }
    
    gameTime--;
    CCLOG("updateBySchedule-gameTime:%d", gameTime);
    CCLOG("updateBySchedule-burstTime: %d", burstTime);
    if (burstTime > 0)
    {
        burstTime--;
    }
    
    gameTimeLabel->setString(StringUtils::toString(gameTime));
    if (burstTime > 0)
    {
        gameTimeLabel->setColor(Color3B::MAGENTA);
    }
    else
    {
        gameTimeLabel->setColor(Color3B(255,255,255));
    }
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
    // ゲームエンドおよびカットインアニメーション時は処理しない
    if (gameEndFlg || burstCutInFlg) return;
    
    // バーストタイム開始
    if (playerInfo->getBp() == Constant::MAX_PLAYER_BP)
    {
        CCLOG("update-ep-break BP: %d", playerInfo->getBp());
        CCLOG("update-ep-break burstTime: %d", burstTime);

        // ボイス再生
        if (GameManager::getInstance()->isBattleModeNormal())
        {
            Constant::StringVector list;
            list = Constant::VOICE_LIST(GameManager::getInstance()->getCharaSelect(),
                                        Constant::Voice::BurstAttack);
            int num = arc4random() % list.size();
            
            SoundManager* soundManager = new SoundManager();
            soundManager->playVoice(list[num]);
        }
        else
        {
            SoundManager* soundManager = new SoundManager();
            Constant::StringVector list;
            Constant::CharaSelect charaSelect;
            int num;
            int burstNum = playerInfo->getBurstCount() % 3;
            switch (burstNum) {
                case 0:
                    charaSelect = Constant::CharaSelect::Conoha;
                    list = Constant::VOICE_LIST(charaSelect, Constant::Voice::BurstAttack);
                    num = arc4random() % list.size();
                    soundManager->playVoice(list[num]);
                    break;
                case 1:
                    charaSelect = Constant::CharaSelect::Anzu;
                    list = Constant::VOICE_LIST(charaSelect, Constant::Voice::BurstAttack);
                    num = arc4random() % list.size();
                    soundManager->playVoice(list[num]);
                    break;
                case 2:
                    list = Constant::VOICE_LIST(Constant::CharaSelect::Conoha, Constant::Voice::BurstAttack);
                    num = arc4random() % list.size();
                    SoundManager* soundManager = new SoundManager();
                    soundManager->playVoice(list[num]);
                    list = Constant::VOICE_LIST(Constant::CharaSelect::Anzu, Constant::Voice::BurstAttack);
                    num = arc4random() % list.size();
                    soundManager->playVoice(list[num]);
                    break;
            }
        }
        
        if (burstTime == 0)
        {
            // カットインアニメーション
            burstCutInFlg = true;
            CallFunc* callback = CallFunc::create([this](){this->startBurstTime();}); // 開始処理を呼び出し
            Sprite* cutInImage;
            int burstNum = playerInfo->getBurstCount() %
                      (GameManager::getInstance()->isBattleModeNormal() ? 2 : 3); // 通常２パターン、ボスバトルは３パターン
            switch (burstNum) {
                case 0:  cutInImage = playerInfo->getCutInImage1(); break;
                case 1:  cutInImage = playerInfo->getCutInImage2(); break;
                case 2:  cutInImage = playerInfo->getCutInImage3(); break;
                default: cutInImage = playerInfo->getCutInImage1(); break;
            }
            
            cutInImage->runAction(
                BattleActionCreator::burstCutIn(cutInImage, callback));
        }
        else
        {
            // バーストタイム中の場合はカットイン省略
            this->startBurstTime();
        }
    }
    
    // 敵撃破
    if (enemyData->getHp() == 0)
    {
        touchOff();
        gameEndFlg = true;
        nodeGrid->runAction(BattleActionCreator::defeatEnemy());
        this->scheduleOnce(schedule_selector(BattleScene::updateByDefeatEnemy), 5.0f);
    }
//    CCLOG("update-end");
}

/**
 *  バースト開始時に行う処理
 *
 */
void BattleScene::startBurstTime()
{
    playerInfo->getCutInImage1()->setVisible(false);
    playerInfo->incrementBurstCount();
    playerInfo->setBp(0);
    burstTime = Constant::MAX_BURST_TIME;

    // バーストによるゲームタイム増加の許容判定
    if (upGameTime < Constant::MAX_UP_GAME_TIME)
    {
        gameTime += Constant::BURST_GAME_TIME_INCREMENT;
        upGameTime += Constant::BURST_GAME_TIME_INCREMENT;

        // ゲームタイムUPエフェクト
        std::string str = "+" + StringUtils::toString(Constant::BURST_GAME_TIME_INCREMENT);
        auto sprite = Label::createWithBMFont(Constant::NORMAL_FONT(), str);
        sprite->setPosition(gameTimeLabel->getContentSize().width / 2, gameTimeLabel->getContentSize().height / 2);
        sprite->setAlignment(TextHAlignment::CENTER);
        sprite->setAnchorPoint(Vec2(-0.5, -1));
        sprite->setScale(BM_FONT_SIZE64(24));
        sprite->setColor(Color3B::MAGENTA);
        this->addChild(sprite);
        
        // エフェクト生成
        sprite->runAction(BattleActionCreator::attackToEnemy());
    }

    burstCutInFlg = false;
}

/**
 *  敵撃破時に行う処理
 *
 *  @param frame フレーム
 */
void BattleScene::updateByDefeatEnemy(float frame)
{
    Constant::StringVector list = Constant::VOICE_LIST(GameManager::getInstance()->getCharaSelect(),
                                                       Constant::Voice::EnemyDefeat);
    int num = arc4random() % list.size();
    
    SoundManager* soundManager = new SoundManager();
    soundManager->playVoice(list[num]);
    
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
    GameManager::getInstance()->tapCount = playerInfo->getTapCount();
    GameManager::getInstance()->burstCount = playerInfo->getBurstCount();

    SoundManager* soundManager = new SoundManager();
    soundManager->stopBGM();
    
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

    // ゲームエンドおよびカットインアニメーション時は処理しない
    if (gameEndFlg || burstCutInFlg) return true;

    // タッチ位置
    auto location = touch->getLocation();

    Constant::StringVector effectList;
    Constant::StringVector battleEffectImageList;
    float scale;
    int damage;             // 与えたダメージ
    int soundEffectNum;     // 効果音
    int hitSpriteNum;       // ヒットエフェクト
    CCLOG("onTouchBegan-burstTime: %d", burstTime);
    CCLOG("onTouchBegan-gameEndFlg: %d", gameEndFlg);
    if (burstTime == 0)
    {
        // 通常時
        effectList = Constant::EFFECT_LIST(Constant::SoundEffect::SoundNormal);
        battleEffectImageList = Constant::BATTLE_EFFECT_IMAGE_LIST(Constant::ImageEffect::ImageNormal);
        scale = 1.0f;
        damage = Constant::BASE_DAMAGE_NORMAL;
        soundEffectNum = arc4random() % effectList.size();
        hitSpriteNum = arc4random() % battleEffectImageList.size();
    }
    else
    {
        // バーストタイム中
        effectList = Constant::EFFECT_LIST(Constant::SoundEffect::SoundBurst);
        battleEffectImageList = Constant::BATTLE_EFFECT_IMAGE_LIST(Constant::ImageEffect::ImageBurst);
        scale = 1.0f;
        damage = Constant::BASE_DAMAGE_BURST;
        soundEffectNum =  arc4random() % effectList.size();
        hitSpriteNum = arc4random() % battleEffectImageList.size();
        
    }
//    Constant::StringVector battleEffectSubImageList =
//    Constant::BATTLE_EFFECT_IMAGE_LIST(Constant::ImageEffect::ImageBurstSub);
//    int hitSpriteSubNum = arc4random() % battleEffectSubImageList.size();
//    Point pos = location;
//    pos.add(Vec2(arc4random() % 100 - 50, arc4random() % 100 - 50));
//    Sprite* effectSubSprite = this->effectManager->effectPurifiedTwice(battleEffectSubImageList[hitSpriteSubNum], pos, scale, 0.05f);
//    
//    this->addChild(effectSubSprite, ZOrder::TouchEffect);
    

    
    // 効果音
    soundManager->playSE(effectList[soundEffectNum]);
    
//    if (arc4random() % 10 == 0)
//    {
//        Constant::StringVector list = Constant::VOICE_LIST(GameManager::getInstance()->getCharaSelect(),
//                                                           Constant::Voice::NormalAttack);
//        int num = arc4random() % list.size();
//        soundManager->playVoice(list[num]);
//    }
    
    // ヒットエフェクト生成
    Sprite* effectSprite = this->effectManager->effectPurified(battleEffectImageList[hitSpriteNum], location, scale);
    this->addChild(effectSprite, ZOrder::TouchEffect);
    
    // 敵のHPゲージ
    auto preHpPercentage = enemyData->getHpPercentage();
    auto afterHp = enemyData->getHp() - damage;
    afterHp = afterHp < 0 ? 0 : afterHp;
    enemyData->setHp(afterHp);
    auto enemyAct = ProgressFromTo::create(0.5, preHpPercentage, enemyData->getHpPercentage());
    enemyHpBar->runAction(enemyAct);
    CCLOG("onTouchBegan-enemyHp:%d / %f%%",enemyData->getHp(), enemyData->getHpPercentage());
    
    // プレイヤータップカウント
    playerInfo->incrementTapCount();
    
    // プレイヤーBPゲージ
    auto preBpPercentage = playerInfo->getBpPercentage();
    playerInfo->upBpGauge();
    auto afterBp = playerInfo->getBp();
    afterBp = afterBp > Constant::MAX_PLAYER_BP ? Constant::MAX_PLAYER_BP : afterBp;
    playerInfo->setBp(afterBp);
    auto playerAct = ProgressFromTo::create(0.5, preBpPercentage, playerInfo->getBpPercentage());
    playerBpBar->runAction(playerAct);
    CCLOG("onTouchBegan-playerBp:%d / %f%%",playerInfo->getBp(), playerInfo->getBpPercentage());
    
    // ダメージ値生成
    std::string damageStr = (burstTime > 0 ? "BURST!!" : "TAP!");
    auto damageNumSprite = Label::createWithBMFont(Constant::NORMAL_FONT(), damageStr);
    damageNumSprite->setPosition(effectSprite->getContentSize().width / 2, effectSprite->getContentSize().height / 2);
    damageNumSprite->setAlignment(TextHAlignment::CENTER);
    damageNumSprite->setAnchorPoint(Vec2(-0.5, -1));
    damageNumSprite->setScale(BM_FONT_SIZE64(24));
    if (burstTime > 0) damageNumSprite->setColor(Color3B::MAGENTA);
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
    
    // ゲームエンドおよびカットインアニメーション時は処理しない
    if (gameEndFlg || burstCutInFlg) return;
    
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
    
    // ゲームエンドおよびカットインアニメーション時は処理しない
    if (gameEndFlg || burstCutInFlg) return;
    
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

    // ゲームエンドおよびカットインアニメーション時は処理しない
    if (gameEndFlg || burstCutInFlg) return;
    
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
//        int damage = Constant::BASE_DAMAGE_NORMAL + arc4random() % Constant::DAMAGE_RANK_UP_INCREMENT;
//
//        // 効果音
//        int num = arc4random() % effectList.size();
//        soundManager->playSE(effectList.at(num));
//
//        // ヒットエフェクト生成
//        num = arc4random() % battleEffectImageList.size();
//        Sprite* effectSprite = this->effectManager->effectPurified(battleEffectImageList.at(num), location);
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
