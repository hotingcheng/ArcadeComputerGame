#include "PlayerFactory.h"

BasePlayerPlane* PlayerFactory::createplayer1()
{
	return new PlayerPlaneMode1;
}

BasePlayerPlane* PlayerFactory::createplayer2()
{
	return new PlayerPlaneMode2;
}


