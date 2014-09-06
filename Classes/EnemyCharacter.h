//
//  EnemyCharacter.h
//  Fragment_of_Eternity
//
//  Created by usr0600205 on 2014/09/06.
//
//

#ifndef __Fragment_of_Eternity__EnemyCharacter__
#define __Fragment_of_Eternity__EnemyCharacter__

#include "cocos2d.h"

class EnemyCharacter : public cocos2d::Ref
{
    
public:
    EnemyCharacter();
    virtual ~EnemyCharacter();
    virtual bool init();
    CREATE_FUNC(EnemyCharacter);
    
protected:
    
private:

};

#endif /* defined(__Fragment_of_Eternity__EnemyCharacter__) */
