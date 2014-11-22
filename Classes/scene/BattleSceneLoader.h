#ifndef __BATTLE_SCENE_LOADER_H__
#define __BATTLE_SCENE_LOADER_H__

#include "scene/BattleScene.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;

class BattleSceneLoader : public LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BattleSceneLoader, loader);
    
    static Scene* createScene();
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(BattleScene);
};
#endif
