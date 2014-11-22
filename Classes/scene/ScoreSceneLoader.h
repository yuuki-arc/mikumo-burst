#ifndef __SCORE_SCENE_LOADER_H__
#define __SCORE_SCENE_LOADER_H__

#include "scene/ScoreScene.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;

class ScoreSceneLoader : public LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ScoreSceneLoader, loader);
    
    static Scene* createScene();
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ScoreScene);
};
#endif
