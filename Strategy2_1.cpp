#include "Strategy2_1.h"


void Strategy2_1::Move(Strategy_Enemy *E, int xdis, int ydis)
{ 
	xdis = -2;
	ydis = 1;
	E->setXY( E->getXPos()+xdis, E->getYPos()+ydis); 
};	
	

void Strategy2_1::TrackPlayerPosition(BasePlayerPlane *PP) 
{
//	PPxPos = PP->getXPos();
//	PPyPos = PP->getYPos();
}

void Strategy2_1::ApproachPlayer(Strategy_Enemy *E)
{
//	int tempx = (PPxPos - E->getXPos()) / (E->getSpeed() * 20);
//	int tempy = (PPyPos - E->getYPos()) / (E->getSpeed() * 20);
	Move(E,-2,1);
}

BaseBullet* Strategy2_1::TimetoAttack(Strategy_Enemy *E)
{
	if ( rand()%250 == 0 )	// if condition is true, attack() to generate a bullet
		return E->Attack();		
	else
		return NULL;
}