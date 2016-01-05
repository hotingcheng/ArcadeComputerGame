#include "Strategy3.h"
#include "BasePlayerPlane.h"


void Strategy3::Move(Strategy_Enemy *E, int xdis, int ydis)
{ 
	E->setXY( E->getXPos()+xdis, E->getYPos()+ydis); 
};	
	

void Strategy3::TrackPlayerPosition(BasePlayerPlane *PP) 
{
	PPxPos = PP->getXPos();
	PPyPos = PP->getYPos();
}

void Strategy3::ApproachPlayer(Strategy_Enemy *E)
{
	// depend on speed of player plane
//	int tempx = (PPxPos - E->getXPos()) / (E->getSpeed() * 25+1);
	int tempy = (PPyPos - E->getYPos()-35) / (E->getSpeed() * 10+1);

	if (E->getXPos() > 450)
		Move(E,-1,tempy);
	else if (E->getXPos() < 450)
		Move(E,2,tempy);
	else
		Move(E,0,tempy);

}

BaseBullet* Strategy3::TimetoAttack(Strategy_Enemy *E)
{
	if ( rand()%50 == 0 || rand()%50 == 1 )	// if condition is true, attack() to generate a bullet
		return E->Attack();		
	else
		return NULL;		
}