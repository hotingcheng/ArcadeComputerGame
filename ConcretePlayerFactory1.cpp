#include "ConcretePlayerFactory1.h"

BasePlayerPlane* ConcretePlayerFactory1::createplayer1()
{
	p1 = new PlayerPlaneMode1;
	return p1;
}

BasePlayerPlane* ConcretePlayerFactory1::createplayer2()
{
	p2 = new PlayerPlaneMode2;
	return p2;
}

void ConcretePlayerFactory1::setTranform()
{
	p1->setNextMode(p2);
	p2->setNextMode(p1);
}
