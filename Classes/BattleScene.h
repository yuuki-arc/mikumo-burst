#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"
#include "EffectManager.h"
#include "EnemyCharacter.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

class BattleScene : public Layer
, public CCBSelectorResolver
, public NodeLoaderListener
{
public:
    BattleScene();
    virtual ~BattleScene();
    
    virtual bool init();
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName);
	virtual void onNodeLoaded(Node* pNode, NodeLoader* pNodeLoader);

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BattleScene, create);
    
    void tappedResultButton(Ref* pTarget, Control::EventType pControlEventType);

    void update(float frame);
    void updateBySchedule(float frame);
    
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event *event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *event);

    void pushBack(Ref* pSender);

private:
    enum ZOrder
    {
        Bg = 0,
        Enemy,
        BattleEffect,
        TouchEffect,
        EnemyHp,
        PersonaHp,
        Status,
        Font,
    };
    
    EffectManager* effectManager;
    MotionStreak *touchEffectMotion;
    std::vector<std::string> enemyImageList = {"f183", "f186", "f189", "f195", "f201", "f207", "f271", "f274", "f277"};
    std::vector<std::string> bgImageList = {"000", "001", "002", "003", "004", "006", "007", "008", "010", "011", "012", "013"};
    std::vector<std::string> battleEffectImageList = {"battleEffect107a", "battleEffect107b", "battleEffect107c", "battleEffect107d", "battleEffect107e", "battleEffect107f", "battleEffect107g", "battleEffect107h", "battleEffect107i", "battleEffect107j"};
    std::vector<std::string> effectList = {"se_battle_blow", "se_battle_darkness", "se_battle_fire", "se_battle_gun", "se_battle_water"};
    
    EnemyCharacter* enemyData;
    ProgressTimer* enemyHpBar;
    Label* gameTimeLabel;
    
    UserDefault* userDefault = UserDefault::getInstance();
    
    int gameTime = 0;
    int current_rank;
    
    void initBackground();
    void initEnemy();
    void initStatusLayer();
    void initTouchEvent();
};

#endif /* defined(__BATTLE_SCENE_H__) */
