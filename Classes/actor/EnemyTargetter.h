#ifndef __10sec_BURST__EnemyTargetter__
#define __10sec_BURST__EnemyTargetter__

#include "cocos2d.h"

USING_NS_CC;

class EnemyTargetter : public Ref
{
private:
    CC_SYNTHESIZE(int, position, Position);
    CC_SYNTHESIZE(int, vector, Vector);
    CC_SYNTHESIZE(int, touch, Touch);
    CC_SYNTHESIZE(Sprite*, image, Image);
    
public:
    EnemyTargetter();
    ~EnemyTargetter();
    static EnemyTargetter* create();
    virtual void setPosition(const Point& pos);
    float radius();
};

#endif /* defined(__10sec_BURST__EnemyEnemyTargetter__) */
