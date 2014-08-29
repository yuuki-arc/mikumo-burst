#ifndef __MENU_SELECT_SCENE_LOADER_H__
#define __MENU_SELECT_SCENE_LOADER_H__

#include "MenuSelectScene.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;

class MenuSelectSceneLoader : public LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MenuSelectSceneLoader, loader);
    
    static Scene* createScene();
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MenuSelectScene);
};
#endif
