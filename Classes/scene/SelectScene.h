#ifndef __SELECT_SCENE_H__
#define __SELECT_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

class SelectScene : public Layer
, public CCBSelectorResolver
, public NodeLoaderListener
{
public:
    SelectScene();
    virtual ~SelectScene();
    
    virtual bool init();
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName);
	virtual void onNodeLoaded(Node* pNode, NodeLoader* pNodeLoader);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SelectScene, create);
    
    void tappedChangeButton(Ref* pTarget, Control::EventType pControlEventType);
    void tappedBattleButton(Ref* pTarget, Control::EventType pControlEventType);
    void tappedBossButton(Ref* pTarget, Control::EventType pControlEventType);
    void tappedScoreButton(Ref* pTarget, Control::EventType pControlEventType);
    
    void pushBack(Ref* pSender);

private:
    enum ZOrder
    {
        Bg = 0,
        Persona,
        PersonaHp,
        Menu,
        Font,
    };
    
    enum Tag
    {
        Character = 0,
        RankStr,
        Rank,
    };
    
    void displayInfo();
    void changeCharacter();
    
    Point charaPos;
};

#endif /* defined(__SELECT_SCENE_H__) */
