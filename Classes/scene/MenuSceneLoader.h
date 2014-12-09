#ifndef __MENU_SCENE_LOADER_H__
#define __MENU_SCENE_LOADER_H__

#include "scene/MenuScene.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;

class MenuSceneLoader : public LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MenuSceneLoader, loader);
    
    static Scene* createScene();
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MenuScene);
};
#endif
