#ifndef __SCORE_SCENE_H__
#define __SCORE_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"
#include "cocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

class MenuData :public cocos2d::Ref{
public:
    
    std::string getCaptionText();
    int getIndex();
    virtual bool init();
    void calcNextIndex();
    void pushCaption(const std::string& str);
    CREATE_FUNC(MenuData);
private:
    int index;
    std::vector<std::string> captions;
    MenuData();
};


class ScoreScene : public Layer
, public CCBSelectorResolver
, public NodeLoaderListener
{
public:
    ScoreScene();
    virtual ~ScoreScene();
    
    virtual bool init();
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName);
    virtual void onNodeLoaded(Node* pNode, NodeLoader* pNodeLoader);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ScoreScene, create);
    
    void tappedScoreButton(Ref* pTarget, Control::EventType pControlEventType);
    void tappedBackButton(Ref* pTarget, Control::EventType pControlEventType);
    
    void pushBack(Ref* pSender);

    
    
    const static int LEADERBOARD_INT = 698;
    const static int LEADERBOARD_FLOAT = 699;
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    

private:
    enum ZOrder
    {
        Bg = 0,
        Status,
        Font,
    };


    cocos2d::Menu* _pMenu;
    
    cocos2d::extension::EditBox* _editBoxInt;
    cocos2d::extension::EditBox* _editBoxFloat;
    cocos2d::LabelTTF* _labelInt;
    cocos2d::LabelTTF* _labelFloat;
    
    cocos2d::Menu* DataStore;
    
    void setSampleUI();
    cocos2d::Menu* getMenu();
    cocos2d::LabelTTF* createLabel(const std::string& text);
    cocos2d::MenuItemLabel* createMenuItem(MenuData* data, const cocos2d::ccMenuCallback& callback);
    cocos2d:: MenuItemLabel* createOpenGameMenu();
    cocos2d:: MenuItemLabel* createWriteIntMenu();
    cocos2d:: MenuItemLabel* createWriteFloatMenu();
    static void AlignVertical(cocos2d::Vector<cocos2d::Node*>& nodes, const cocos2d::Point& top,float margin);
    cocos2d::MenuItemLabel* createReadIntMenu();
    cocos2d::MenuItemLabel* createReadFloatMenu();
    void readIntFromLB();
    void readFloatFromLB();

};

#endif /* defined(__Score_SCENE_H__) */
