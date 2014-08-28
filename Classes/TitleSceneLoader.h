#ifndef __TITLE_SCENE_LOADER_H__
#define __TITLE_SCENE_LOADER_H__

#include "TitleScene.h"
#include "extensions/cocos-ext.h"

USING_NS_CC_EXT;

class TitleSceneLoader : public LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TitleSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TitleScene);
};

#endif
