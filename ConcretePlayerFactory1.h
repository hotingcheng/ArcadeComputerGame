#ifndef CONCRETEPLAYERFACTORY1_H
#define CONCRETEPLAYERFACTORY1_H

#include "PlayerFactory.h"


class ConcretePlayerFactory1 : public PlayerFactory
{
public:
	virtual BasePlayerPlane* createplayer1();
	virtual BasePlayerPlane* createplayer2();

	virtual void setTranform();
};

#endif