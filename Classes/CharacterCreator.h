#ifndef __Fragment_of_Eternity__CharacterCreator__
#define __Fragment_of_Eternity__CharacterCreator__

#include "cocos2d.h"

USING_NS_CC;

enum CharacterScale {
    ALL  = 100,
    HARF = 60,
};

class CharacterCreator
{
    
public:
    CharacterCreator();
    virtual ~CharacterCreator();

    void init(CharacterScale scale);
    Sprite* create(const std::string &filename);
    Sprite* create(const std::string &filename, Point position);

private:
    CharacterScale scale;

};

#endif /* defined(__Fragment_of_Eternity__CharacterCreator__) */
