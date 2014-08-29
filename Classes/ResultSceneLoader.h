#ifndef __RESULT_SCENE_LOADER_H__
#define __RESULT_SCENE_LOADER_H__

#include "ResultScene.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;

class ResultSceneLoader : public LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ResultSceneLoader, loader);

    static Scene* createScene();
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ResultScene);
};
#endif
