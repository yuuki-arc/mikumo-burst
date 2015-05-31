#ifndef __LOADING_SCENE_LOADER_H__
#define __LOADING_SCENE_LOADER_H__

#include "scene/LoadingScene.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;

class LoadingSceneLoader : public LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LoadingSceneLoader, loader);
    
    static Scene* createScene();
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LoadingScene);
};
#endif
