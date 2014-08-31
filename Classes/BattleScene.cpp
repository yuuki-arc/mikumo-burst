#include "BattleScene.h"
#include "ResultSceneLoader.h"

BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}

bool BattleScene::init(){
    if(!CCLayer::init())
    {
        return false;
    }

    //MotionStreakを作成
    m_pStreak = MotionStreak::create(1.0, 1.0f, 50.0f, Color3B::GREEN, "effect/pipo-btleffect063.png");
    addChild(m_pStreak);
 
    //イベントリスナー作成
    auto listener = EventListenerTouchAllAtOnce::create();
    
    //イベントを飲み込むかどうか
//    listener->setSwallowTouches(true);
 
    listener->onTouchesBegan = CC_CALLBACK_2(BattleScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(BattleScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(BattleScene::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    schedule(schedule_selector(BattleScene::updateBySchedule), 3.0f);
    
    return true;
}

void BattleScene::update( float frame )
{
//    CCLOG("フレーム単位で呼び出される");
}

void BattleScene::updateBySchedule( float frame )
{
    CCLOG("一定間隔（スケジュール）で呼び出される");
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

void BattleScene::tappedResultButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedResultButton eventType = %d", pControlEventType);
    Scene* scene = ResultSceneLoader::createScene();
    TransitionProgressInOut* trans = TransitionProgressInOut::create(1, scene);
    Director::getInstance()->replaceScene(trans);
}

void BattleScene::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        
        Point pos = this->convertTouchToNodeSpace(touch);
        this->m_pStreak->setPosition(pos);

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

        Point pos = this->convertTouchToNodeSpace(touch);
        this->m_pStreak->setPosition(pos);
        
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
