#ifndef __Fragment_of_Eternity__CharacterCreator__
#define __Fragment_of_Eternity__CharacterCreator__

#include "cocos2d.h"

USING_NS_CC;

enum CharacterScale {
    ALL  = 100,
    HARF = 75,
};

class CharacterCreator
{
    
public:
    CharacterCreator();
    virtual ~CharacterCreator();
    
    Sprite* create(const std::string &filename, CharacterScale scale = ALL);
};

#endif /* defined(__Fragment_of_Eternity__CharacterCreator__) */
