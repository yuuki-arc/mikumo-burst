//
// RewardScene.h
//
// appC cloud Plugin Cocos2d-x example
// Created by cayto inc.
//


#ifndef __REWARD_SCENE_H__
#define __REWARD_SCENE_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocosGUI.h"
#include <string>
#include <vector>

/**
 *  表示のためのデータ
 */
class MenuData :public cocos2d::Ref{
public:
    
    std::string getCaptionText();
    int getIndex();
    virtual bool init();
    void calcNextIndex();
    void pushCaption(const std::string& str);
    CREATE_FUNC(MenuData);
private:
    int index;
    std::vector<std::string> captions;
    MenuData();
};
/**
 *  リワードシーン
 */
class Reward : public cocos2d::Layer
{
public:
    const static std::string SERVICEID_01;
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Reward);
    
private:
    cocos2d::Menu* _pMenu;
    cocos2d::LabelTTF* _labelStatusS1;
    cocos2d::Menu* getMenu();

    void setSampleUI();
    cocos2d::MenuItemLabel* createMenuItem(MenuData* , const cocos2d::ccMenuCallback& );
    cocos2d::LabelTTF* createLabel(const std::string& );
    void viewInfo();
    cocos2d::MenuItemLabel* createMenuItemDisplayService();
    cocos2d::MenuItemLabel* createMenuItemDisplayPointService();
    cocos2d::MenuItemLabel* createMenuItemReloadServiceStatus();
    cocos2d::MenuItemLabel* createMenuItemResetServiceStatus();
};

#endif // __REWARD_SCENE_H__
