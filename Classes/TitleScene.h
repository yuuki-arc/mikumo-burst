//
//  TitleScene.h
//

#ifndef __Hoge__TitleScene__
#define __Hoge__TitleScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

class TitleScene : public Layer
, public CCBSelectorResolver /** CocosBuilderからメニューを取得するのに必要 */
{
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName);

    void tappedStartButton(Object * pTarget, Control::EventType pControlEventType);

public:
    // コンストラクタ、デストラクタ
    TitleScene();
    virtual ~TitleScene();
    
    // createメソッド
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TitleScene, create);
};

#endif /* defined(__Hoge__TitleScene__) */
