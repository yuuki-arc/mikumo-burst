//
//  Scale9SpriteWrapper.cpp
//  mikumo-burst
//
//  Created by m.yamaoka on 2015/06/06.
//
//

#include "Scale9SpriteWrapper.h"

#include "cocos-ext.h"
using namespace cocos2d;
USING_NS_CC_EXT;

Scale9SpriteWrapper* Scale9SpriteWrapper::createWithSpriteFrameName(const char *$fileName, float $perWidth, float $perHeight){
    Scale9SpriteWrapper* spr = new Scale9SpriteWrapper();
    if(spr && spr->initWithSpriteFrameName($fileName, $perWidth, $perHeight)){
        spr->autorelease();
        return spr;
    }
    delete spr;
    spr = NULL;
    return NULL;
};

bool Scale9SpriteWrapper::initWithSpriteFrameName(const char *$fileName, float $perWidth, float $perHeight){
    SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName($fileName);
    float width = frame->getRect().size.width;
    float height = frame->getRect().size.height;
    
    float perWidth = width / 100.0f * $perWidth;
    float perHeight = height / 100.0f * $perHeight;
    
    const Rect capInsents = Rect(perWidth , perHeight , width - perWidth * 2 , height - perHeight * 2);
    
    return ui::Scale9Sprite::initWithSpriteFrame(frame, capInsents);
}

Scale9SpriteWrapper* Scale9SpriteWrapper::createWithFile(const char *$fileName, float $perWidth, float $perHeight){
    Scale9SpriteWrapper* spr = new Scale9SpriteWrapper();
    if(spr && spr->initWithFile($fileName, $perWidth, $perHeight)){
        spr->autorelease();
        return spr;
    }
    delete spr;
    spr = NULL;
    return NULL;
};

bool Scale9SpriteWrapper::initWithFile(const char *$fileName, float $perWidth, float $perHeight){
    Texture2D* texture = Director::getInstance()->getTextureCache()->addImage($fileName);
    if(texture){
        float width = texture->getContentSize().width;
        float height = texture->getContentSize().height;
        float perWidth = width / 100.0f * $perWidth;
        float perHeight = height / 100.0f * $perHeight;
        
        const Rect capInsents = Rect(perWidth , perHeight , width - perWidth * 2 , height - perHeight * 2);
        const Rect capRect = Rect(0,0,width,height);
        SpriteBatchNode* node = SpriteBatchNode::createWithTexture(texture , 9);
        
        auto sprite = Sprite::createWithTexture(node->getTexture());
        return init(sprite, capRect, false, capInsents);
    }
    return false;
}