#ifndef __Fragment_of_Eternity__SoundManager__
#define __Fragment_of_Eternity__SoundManager__

#include "cocos2d.h"

class SoundManager
{
public:
    SoundManager();
    virtual ~SoundManager();
    bool init();
    void playBGM(std::string soundName);
    void preloadSE(const std::string &id);
    unsigned int playSE(const std::string &id);
private:
    std::string ext;
    const char* getFileName(const std::string &id);
};

#endif /* defined(__Fragment_of_Eternity__SoundManager__) */
