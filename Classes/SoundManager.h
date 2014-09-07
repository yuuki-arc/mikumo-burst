#ifndef __Fragment_of_Eternity__SoundManager__
#define __Fragment_of_Eternity__SoundManager__

#include "cocos2d.h"

class SoundManager
{
public:
    SoundManager();
    virtual ~SoundManager();
    bool init();
    void playBGM(const std::string soundName, bool forceStart = false);
    void preloadSE(const std::string seName);
    void playSE(const std::string seName);
};

#endif /* defined(__Fragment_of_Eternity__SoundManager__) */
