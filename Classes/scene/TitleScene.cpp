#include "scene/TitleScene.h"
#include "scene/SelectSceneLoader.h"
#include "tools/GoogleAnalyticsTracker.h"
#include "resources/SoundManager.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

bool TitleScene::init()
{    
    CCLOG("TitleScene::init");
    GoogleAnalyticsTracker::sendScreen("TitleScene");
	if(!Layer::init())
	{
		return false;
	}
    
	return true;
}

SEL_MenuHandler TitleScene::onResolveCCBCCMenuItemSelector(Ref *pTarget, const char *pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    return NULL;
}

Control::Handler TitleScene::onResolveCCBCCControlSelector(Ref *pTarget, const char *pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedStartButton", TitleScene::tappedStartButton);
    return NULL;
}

void TitleScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    CCLOG("TitleScene::onNodeLoaded");
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    Size screenSize = director->getWinSize();
    
    // BGM
    SoundManager* soundManager = new SoundManager();
    soundManager->playBGM("bgm_title");
    
    // SE
    soundManager->preloadSE("se_select");
    
    // エフェクト
    ParticleSystemQuad* particle1 = ParticleSystemQuad::create("particle/title_particle1.plist");
    particle1->setPosition(Vec2(screenSize.width * 14 / 40, screenSize.height * 13 / 40));
    this->addChild(particle1);
    ParticleSystemQuad* particle2 = ParticleSystemQuad::create("particle/title_particle2.plist");
    particle2->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(particle2);
    
    //        ParticleSystemQuad* particle1 = ParticleSystemQuad::create("particle/title_particle1.plist");
    //        particle1->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    //        ParticleSystemQuad* particle2 = ParticleSystemQuad::create("particle/title_particle2.plist");
    //        particle2->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    //
    //        ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(particle1->getTexture());
    //
    //        batch->addChild(particle1, 0);
    //        batch->addChild(particle2, 0);
    //
    //        pScene->addChild(batch);
}

void TitleScene::tappedStartButton(Ref *pTarget, Control::EventType pControlEventType)
{
    CCLOG("tappedStartButton eventType = %d", pControlEventType);
    SoundManager* soundManager = new SoundManager();
    soundManager->playSE("se_select");

    // テクスチャアトラスを読み込む
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("character/enemy2/enemy2.plist");
    frameCache->addSpriteFramesWithFile("character/persona2/persona2.plist");
    frameCache->addSpriteFramesWithFile("misc/misc.plist");
    frameCache->addSpriteFramesWithFile("effect/battleEffectB0.plist");
    

    Scene* scene = SelectSceneLoader::createScene();
    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
    Director::getInstance()->replaceScene(trans);
}

