//
//  Scale9SpriteWrapper.h
//  mikumo-burst
//
//  Created by m.yamaoka on 2015/06/06.
//
//

#ifndef __mikumo_burst__Scale9SpriteWrapper__
#define __mikumo_burst__Scale9SpriteWrapper__

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
USING_NS_CC_EXT;

class Scale9SpriteWrapper : public ui::Scale9Sprite {
public:
    /**
     * スプライトフレームから作成
     */
    static Scale9SpriteWrapper* createWithSpriteFrameName(const char* $fileName , float $perWidth , float $perHeight);
    static Scale9SpriteWrapper* createWithSpriteFrameName(const char* $fileName , float $percentage){
        return createWithSpriteFrameName($fileName , $percentage , $percentage);
    }
    virtual bool initWithSpriteFrameName(const char* $fileName , float $perWidth , float $perHeight);
    
    /**
     *  ファイルから作成
     */
    static Scale9SpriteWrapper* createWithFile(const char* $fileName , float $perWidth , float $perHeight);
    static Scale9SpriteWrapper* createWithFile(const char* $fileName , float $percentage){
        return createWithFile($fileName , $percentage , $percentage);
    }
    virtual bool initWithFile(const char* $fileName , float $perWidth , float $perHeight);
};

#endif /* defined(__mikumo_burst__Scale9SpriteWrapper__) */
