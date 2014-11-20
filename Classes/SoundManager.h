#ifndef __10sec_BURST__SoundManager__
#define __10sec_BURST__SoundManager__

#include "cocos2d.h"

class SoundManager
{
public:
    SoundManager();
    virtual ~SoundManager();
    bool init();
    void playBGM(const std::string soundName, bool forceStart = false);
    void stopBGM();
    void preloadSE(const std::string seName);
    void playSE(const std::string seName);
    void preloadVoice(const std::string voiceName);
    void playVoice(const std::string voiceName);
};

#endif /* defined(__10sec_BURST__SoundManager__) */
