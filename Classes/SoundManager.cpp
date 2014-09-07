#include "SoundManager.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

bool SoundManager::init()
{
    //    SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
    //    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
    //    SimpleAudioEngine::end();
    
    return true;
}

void SoundManager::playBGM(const std::string musicName, bool forceStart)
{
    auto audioEngine = SimpleAudioEngine::getInstance();
    if (forceStart)
    {
        audioEngine->stopBackgroundMusic();
    }
    if (!audioEngine->isBackgroundMusicPlaying())
    {
        std::string musicFileName = "sound/" + musicName + ".mp3";
        audioEngine->preloadBackgroundMusic(musicFileName.c_str());
        audioEngine->playBackgroundMusic(musicFileName.c_str(), true);
    }
}

void SoundManager::preloadSE(const std::string seName)
{
    std::string seFileName = "sound/" + seName + ".mp3";
    SimpleAudioEngine::getInstance()->preloadEffect(seFileName.c_str());
}

void SoundManager::playSE(const std::string seName)
{
    std::string seFileName = "sound/" + seName + ".mp3";
    SimpleAudioEngine::getInstance()->playEffect(seFileName.c_str(), false, 1.0f, 0.0f, 1.0f);
}
