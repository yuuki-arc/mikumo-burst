#include "SelectScene.h"
#include "BattleSceneLoader.h"
#include "CharacterCreator.h"
#include "SoundManager.h"

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

bool SelectScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	return true;
}

SEL_MenuHandler SelectScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    return NULL;
}

Control::Handler SelectScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBattleButton", SelectScene::tappedBattleButton);
    return NULL;
}

void SelectScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    // BGM
    SoundManager* soundManager = new SoundManager();
    soundManager->playBGM("bgm_title", true);
    
    // SE
    soundManager->preloadSE("se_select");

    auto label = LabelBMFont::create("RESULT", "Arial_Black.fnt");
    label->setPosition(Point(200,200));
    this->addChild(label, ZOrder::Font);
 
    // キャラ
    int num = CCRANDOM_0_1() * personaImageList.size();
    std::string personaFileName = StringUtils::format("%s.png", personaImageList.at(num).c_str());
    
    CharacterCreator* creator = new CharacterCreator();
    Sprite* character = creator->create(personaFileName, CharacterScale::HARF);
    this->addChild(character, ZOrder::Persona);
}

void SelectScene::tappedBattleButton(Ref* pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedBattleButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");
    
    Scene* scene = BattleSceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}
