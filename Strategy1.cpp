#include "Strategy1.h"

Strategy1::Strategy1(int x, int y)
{
	movex = x;
	movey = y;
}

void Strategy1::Move(Strategy_Enemy *E, int xdis, int ydis)
{ 
//	xdis = -2;
//	ydis = 0;
//	E->setXY( E->getXPos()+xdis, E->getYPos()+ydis); 
	E->setXY( E->getXPos()+movex, E->getYPos()+movey); 
};	
	

void Strategy1::TrackPlayerPosition(BasePlayerPlane *PP) 
{
//	PPxPos = PP->getXPos();
//	PPyPos = PP->getYPos();
}

void Strategy1::ApproachPlayer(Strategy_Enemy *E)
{
//	int tempx = (PPxPos - E->getXPos()) / (E->getSpeed() * 20);
//	int tempy = (PPyPos - E->getYPos()) / (E->getSpeed() * 20);
	Move(E,-2,0);
}

BaseBullet* Strategy1::TimetoAttack(Strategy_Enemy *E)
{
	if ( rand()%90 == 0 )	// if condition is true, attack() to generate a bullet
		return E->Attack();		
	else return NULL;
}