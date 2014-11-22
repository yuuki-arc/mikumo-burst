#include "EnemyTargetter.h"

USING_NS_CC;

EnemyTargetter::EnemyTargetter()
: position(0)
, image(nullptr)
{
}

EnemyTargetter::~EnemyTargetter()
{
}

EnemyTargetter* EnemyTargetter::create()
{
    EnemyTargetter *character = new EnemyTargetter();
    character->autorelease();
    
    return character;
}

void EnemyTargetter::setPosition(const Point& pos)
{
    getImage()->setPosition(pos);
//    if (!getImage()-> m_nextPosition.equals(pos))
//        m_nextPosition = pos;
}

float EnemyTargetter::radius()
{
    return getImage()->getTexture()->getContentSize().width * 0.5f;
}
