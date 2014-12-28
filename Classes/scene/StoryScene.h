#ifndef __STORY_SCENE_H__
#define __STORY_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"
#include "core/Constant.h"
#include "core/LabelAttributedBMFont.h"
#include "resources/JsonLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

class StoryScene : public Layer
, public CCBSelectorResolver
, public NodeLoaderListener
{
public:
    StoryScene();
    virtual ~StoryScene();
    
    virtual bool init();
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName);
    virtual void onNodeLoaded(Node* pNode, NodeLoader* pNodeLoader);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(StoryScene, create);
    
//    void tappedBackButton(Ref* pTarget, Control::EventType pControlEventType);
    
    void update(float frame);
    void pushBack(Ref* pSender);
    
private:
    enum ZOrder
    {
        Bg = 0,
        Menu,
        Status,
        Font,
    };
    std::vector<std::string> bgImageList;

    void initBackground();
    bool loadScenario();
    void initStoryMessages();
    Constant::StringVector setStoryMessages();
//    void setCallbackChangedPage( const std::function<void( int )> &callback );
    
    enum LoadStatus
    {
        BeforeLoad = 0,
        DataDownload,
        ReadError,
        ReadSuccess,
        LoadComplete,
    };
    LoadStatus loadStatus = LoadStatus::BeforeLoad;
    
    JsonLoader* loader;
    LabelAttributedBMFont* label;
};

#endif /* defined(__STORY_SCENE_H__) */
