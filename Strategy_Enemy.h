#ifndef STRATEGY_ENEMY_H
#define STRATEGY_ENEMY_H

#include "BaseBullet.h"

class Strategy_Enemy
{
public:
	virtual const void setXY( const int, const int )=0;
	virtual BaseBullet* Attack()=0;
	virtual int getXPos() const=0;
	virtual int getYPos() const=0;
	virtual int getSpeed() const=0;
};

#endif
