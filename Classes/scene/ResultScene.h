#ifndef __RESULT_SCENE_H__
#define __RESULT_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"
#include "resources/UserDataStore.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

class ResultScene : public Layer
, public CCBSelectorResolver
, public NodeLoaderListener
{
public:
    ResultScene();
    virtual ~ResultScene();
    
    virtual bool init();
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName);
	virtual void onNodeLoaded(Node* pNode, NodeLoader* pNodeLoader);

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ResultScene, create);
    
    void tappedSelectButton(Ref* pTarget, Control::EventType pControlEventType);
    void tappedSocialButton(Ref* pTarget, Control::EventType pControlEventType);
    void tappedRewardButton(Ref* pTarget, Control::EventType pControlEventType);
    void tappedMoreGamesButton(Ref* pTarget, Control::EventType pControlEventType);

    void pushBack(Ref* pSender);

private:
    enum ZOrder
    {
        Bg = 0,
        Menu,
        Font,
    };
    
    void saveData(int battleRank, StringMapVector charaRankList, int score, int burstCount);
    void saveGamers();
    void displayInfo(int battleRank, StringMapVector charaRankList, int score, int burstCount);
};

#endif /* defined(__Result_SCENE_H__) */
