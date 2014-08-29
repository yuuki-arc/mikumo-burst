#ifndef __SELECT_SCENE_LOADER_H__
#define __SELECT_SCENE_LOADER_H__

#include "SelectScene.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;

class SelectSceneLoader : public LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SelectSceneLoader, loader);
    
    static Scene* createScene();
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SelectScene);
};
#endif
