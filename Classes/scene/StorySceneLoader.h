#ifndef __STORY_SCENE_LOADER_H__
#define __STORY_SCENE_LOADER_H__

#include "scene/StoryScene.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;

class StorySceneLoader : public LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(StorySceneLoader, loader);
    
    static Scene* createScene();
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(StoryScene);
};
#endif
