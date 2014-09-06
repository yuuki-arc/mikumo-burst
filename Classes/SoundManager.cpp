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
    ext = ".mp3";
    //    SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
    //    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
    //    SimpleAudioEngine::end();
    
    return true;
}

void SoundManager::playBGM(std::string musicName)
{
    auto audioEngine = SimpleAudioEngine::getInstance();
    if (!audioEngine->isBackgroundMusicPlaying())
    {
        std::string musicFileName = "sound/" + musicName + ".mp3";
        audioEngine->playBackgroundMusic(musicFileName.c_str(), true);
    }
}

void SoundManager::preloadSE(const std::string &id)
{
    SimpleAudioEngine::getInstance()->preloadEffect(getFileName(id));
}

unsigned int SoundManager::playSE(const std::string &id)
{
    return SimpleAudioEngine::getInstance()->playEffect(getFileName(id), false, 1.0f, 0.0f, 1.0f);
}

const char* SoundManager::getFileName(const std::string &id)
{
    std::string tmp;
    tmp += id;
    tmp += ext;
    return tmp.data();
}
