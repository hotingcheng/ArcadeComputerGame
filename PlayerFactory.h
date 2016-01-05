#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H


#include "BasePlayerPlane.h"
#include "PlayerPlaneMode1.h"
#include "PlayerPlaneMode2.h"


class PlayerFactory
{
protected:	
	BasePlayerPlane* p1;
	BasePlayerPlane* p2;
	BasePlayerPlane* p3;
	BasePlayerPlane* p4;
	BasePlayerPlane* p5;
	BasePlayerPlane* p6;
	BasePlayerPlane* p7;
	BasePlayerPlane* p8;
	BasePlayerPlane* p9;
	BasePlayerPlane* p10;

public:
	virtual BasePlayerPlane* createplayer1() {return NULL;};
	virtual BasePlayerPlane* createplayer2() {return NULL;};
	virtual BasePlayerPlane* createplayer3() {return NULL;};
	virtual BasePlayerPlane* createplayer4() {return NULL;};
	virtual BasePlayerPlane* createplayer5() {return NULL;};
	virtual BasePlayerPlane* createplayer6() {return NULL;};
	virtual BasePlayerPlane* createplayer7() {return NULL;};
	virtual BasePlayerPlane* createplayer8() {return NULL;};
	virtual BasePlayerPlane* createplayer9() {return NULL;};
	virtual BasePlayerPlane* createplayer10() {return NULL;};

	virtual void setTranform() {};
};

#endif