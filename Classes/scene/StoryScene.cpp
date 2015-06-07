#include "scene/StoryScene.h"
#include "scene/SelectSceneLoader.h"
#include "tools/GoogleAnalyticsTracker.h"
#include "core/Constant.h"
#include "core/GameManager.h"
#include "resources/SoundManager.h"
#include "factory/CharacterCreator.h"
#include "factory/TextCreator.h"
#include "tools/NativeLauncher.h"
#include "core/LabelAttributedBMFont.h"
#include "resources/DownloadCacheManager.h"
#include "resources/AppsInformation.h"

StoryScene::StoryScene()
: bgImageList(Constant::BG_IMAGE_LIST())
, scenarioCache(nullptr)
{
}

StoryScene::~StoryScene()
{
    CC_SAFE_RELEASE_NULL(scenarioCache);
}

bool StoryScene::init()
{
//    GoogleAnalyticsTracker::sendScreen("StoryScene");
    if(!Layer::init())
    {
        return false;
    }
    
    initBackground();
    
    scenarioCache = DownloadCacheManager::create();
    scenarioCache->retain();
    scenarioCache->setUrl(__SHEET_URL_STORY);
    scenarioCache->setFileName(Constant::CACHE_FILE_STORY());
    scenarioCache->setCallback([this](Ref *sender){initStoryMessages();});
    
    return true;
}

SEL_MenuHandler StoryScene::onResolveCCBCCMenuItemSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
    
    return NULL;
}

Control::Handler StoryScene::onResolveCCBCCControlSelector(Ref* pTarget, const char* pSelectorName)
{
    CCLOG("name = %s", pSelectorName);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedBackButton", StoryScene::tappedBackButton);
    return NULL;
}

void StoryScene::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    // スプライト読み込み
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("character/persona2/persona2.plist");
    frameCache->addSpriteFramesWithFile("misc/misc.plist");

    // SE
    SoundManager* soundManager = new SoundManager();
    soundManager->preloadSE("se_select");

    // シナリオデータ取得
    this->loadScenario();
    
    // メニュー表示
    float labelWidth = origin.x + visibleSize.width / 2;
    float relativeLabelHeight = 25.0f;
    Point point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 100);
    Sprite* windowSprite = Sprite::createWithSpriteFrameName("menu_window.png");
    windowSprite->setPosition(point);
    windowSprite->setScale(windowSprite->getScale(),
                           windowSprite->getScale() * 40 / 100);
    addChild(windowSprite, ZOrder::Menu);

    // キャラクター表示
    Point charaPos = Point(origin.x + visibleSize.width * 2 / 3,
                           origin.y + visibleSize.height * 65 / 100);
    CharacterCreator* creator = new CharacterCreator();
    creator->init(CharacterScale::HARF);
    Sprite* character = creator->create("persona_conoha.png", charaPos);
    character->setTag(Tag::Character);
    character->setVisible(false);
    this->addChild(character, ZOrder::Persona);
    
    // スケジュール更新
    this->scheduleUpdate();    
}

/**
 背景を初期化
 */
void StoryScene::initBackground()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
//    int num = arc4random() % bgImageList.size();
    int num = 1;
    Sprite* background = Sprite::createWithSpriteFrameName(StringUtils::format("%s.png", bgImageList.at(num).c_str()));
    background->setPosition(Point(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height / 2));
    
    float scale = Director::getInstance()->getContentScaleFactor();
    background->setScale(background->getScale()*scale, background->getScale()*scale);
    
    this->addChild(background, ZOrder::Bg);
}

bool StoryScene::loadScenario()
{
//    AppsInformation* appsInfo = AppsInformation::create();
//    appsInfo->downloadData();
//    CCLOG("updateShhetDate: %s", GameManager::getInstance()->appsInfo->getUpdateSheetDate().c_str());
    
    bool result = scenarioCache->loadData();
    return result;
}

/**
 *  定期更新（フレーム毎）
 *
 *  @param frame フレーム
 */
void StoryScene::update(float frame)
{
    bool result = scenarioCache->execCallbackReferenceData();
    if (!result)
    {
        CCLOG("StoryScene::read error");
    }
}

void StoryScene::initStoryMessages()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // 表示文字準備
    this->setStoryData();
    
    float labelWidth = origin.x + visibleSize.width * 1 / 10;
    float relativeLabelHeight = 2.5f;
    Point point = Point(labelWidth, origin.y + visibleSize.height * relativeLabelHeight / 10);
    label = TextCreator::create(this->storyMessages, point);
    label->setScale(BM_FONT_SIZE64(16));
    this->addChild(label, ZOrder::Font);
    
    // コールバック設定するなら(全表示が終わったときにタップされると呼ばれる)
    label->setCallback([this](Ref *sender){
        // 処理記述
        CCLOG("setCallback");
        AppsInformation* appsInfo = AppsInformation::create();
        appsInfo->retain();
        appsInfo->downloadData(Constant::CACHE_FILE_APPS());
    });
    
    // コールバック設定その２(ページ送りするたびに呼ばれる)
    // もどってくる値はstoryMessagesのindex
    label->setCallbackChangedPage([this](int index) {
        // indexから現在何が表示されているのか判定して何か処理
        // ページ送りされたらなので、indexは1から(2ページ目からしかこない)
        CCLOG("setCallbackChangedPage");
        this->displayStoryCharacter(this->storyCharacters[index].c_str());
    });
    
    // 文字送りしない場合(ページ送りとキーワード強調は有効にしたい場合)
    // label->setDispSpeed(0);
    
    // 文字送り開始(これやんないと何も始まらないYo)
    label->start();
}

void StoryScene::setStoryData()
{
    picojson::object& sheets = scenarioCache->loader->jsonResult.get<picojson::object>();
    picojson::array& sheetColumns = sheets["sc0"].get<picojson::array>();
    for (picojson::array::iterator it = sheetColumns.begin(); it != sheetColumns.end(); it++)
    {
        picojson::object& column = it->get<picojson::object>();
        int mainId = (int)column["main_id"].get<double>();
        int subId = (int)column["sub_id"].get<double>();
        std::string charaName = (std::string)column["chara_name"].get<std::string>();
        std::string message = (std::string)column["message"].get<std::string>();
        
        this->storyCharacters.push_back(charaName);
        this->storyMessages.push_back(message);
        CCLOG("x:%d, y:%d, z:%s", mainId, subId, charaName.c_str());
    }
}

void StoryScene::displayStoryCharacter(const std::string &charaName)
{
    Constant::StringVector personaList = Constant::PERSONA_IMAGE_LIST(Constant::ImagePersona::PersonaStory);
    int num = charaName == "このは" ? 0 : (charaName == "あんず" ? 1 : 2);
    CCLOG("name:%s, num:%d", charaName.c_str(), num);
    std::string personaFileName = StringUtils::format("%s.png", personaList[num].c_str());
    Sprite* character = (Sprite*)this->getChildByTag(Tag::Character);

    CharacterCreator* creator = new CharacterCreator();
    if (num == 2)
    {
        character->setVisible(false);
    }
    else
    {
        creator->init(CharacterScale::HARF);
        creator->change(character, personaFileName);
        character->setVisible(true);
    }
}

//void StoryScene::tappedBackButton(Ref* pTarget, Control::EventType pControlEventType)
//{
//    CCLOG("tappedBackButton eventType = %d", pControlEventType);
//    SoundManager* soundManager = new SoundManager();
//    soundManager->playSE("se_select");
//    
//    Scene* scene = SelectSceneLoader::createScene();
//    TransitionCrossFade* trans = TransitionCrossFade::create(0.5, scene);
//    Director::getInstance()->replaceScene(trans);
//}
