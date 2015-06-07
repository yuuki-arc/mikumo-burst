#ifndef __SELECT_STORY_SCENE_LOADER_H__
#define __SELECT_STORY_SCENE_LOADER_H__

#include "scene/SelectStoryScene.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;

class SelectStorySceneLoader : public LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SelectStorySceneLoader, loader);
    
    static Scene* createScene();
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SelectStoryScene);
};
#endif
