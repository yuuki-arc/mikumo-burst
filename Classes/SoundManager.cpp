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
        std::string fileName = "sound/" + musicName + ".mp3";
        audioEngine->preloadBackgroundMusic(fileName.c_str());
        audioEngine->playBackgroundMusic(fileName.c_str(), true);
    }
}

void SoundManager::preloadSE(const std::string seName)
{
    std::string fileName = "sound/" + seName + ".mp3";
    SimpleAudioEngine::getInstance()->preloadEffect(fileName.c_str());
}

void SoundManager::playSE(const std::string seName)
{
    std::string fileName = "sound/" + seName + ".mp3";
    SimpleAudioEngine::getInstance()->playEffect(fileName.c_str(), false, 1.0f, 0.0f, 1.0f);
}

void SoundManager::preloadVoice(const std::string voiceName)
{
    std::string fileName = "voice/" + voiceName + ".wav";
    SimpleAudioEngine::getInstance()->preloadEffect(fileName.c_str());
}

void SoundManager::playVoice(const std::string voiceName)
{
    std::string fileName = "voice/" + voiceName + ".wav";
    SimpleAudioEngine::getInstance()->playEffect(fileName.c_str(), false, 1.0f, 0.0f, 1.0f);
}
