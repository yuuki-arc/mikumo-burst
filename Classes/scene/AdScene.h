#ifndef __AD_SCENE_H__
#define __AD_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <string>

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

class Ad : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    cocos2d::Menu* getMenu();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Ad);
private:
    cocos2d::MenuItemLabel* createMenuCloseAll();
    cocos2d::MenuItemLabel* createMenuList();
    cocos2d::MenuItemLabel* createMenuCutin();
    cocos2d::MenuItemLabel* createMenuMaquee();
    cocos2d::MenuItemLabel* createMenuMove();
    cocos2d::MenuItemLabel* createMenuSimple();
    cocos2d::MenuItemLabel* createMenuMatchBanner();
    
    cocos2d::Menu* _pMenu;
    void setSampleUI();

    cocos2d::LabelTTF* createLabel(const std::string& text);
    cocos2d::MenuItemLabel* createMenuItem(MenuData* data, const cocos2d::ccMenuCallback& callback);
};
#endif // __HELLOWORLD_SCENE_H__
