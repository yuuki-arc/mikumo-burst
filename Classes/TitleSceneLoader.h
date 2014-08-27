//
//  TitleSceneLoader.h
//

#ifndef Hoge_TitleSceneLoader_h
#define Hoge_TitleSceneLoader_h

#include "TitleScene.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

class TitleSceneLoader : public LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TitleSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(TitleScene);
};

#endif
