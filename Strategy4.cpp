#include "Strategy4.h"
#include "BasePlayerPlane.h"

void Strategy4::Move(Strategy_Enemy *E, int xdis, int ydis)
{ 
	E->setXY( E->getXPos()+xdis, E->getYPos()+ydis); 	
};	
	

void Strategy4::TrackPlayerPosition(BasePlayerPlane *PP) 
{
	PPxPos = PP->getXPos();
	PPyPos = PP->getYPos();
}

void Strategy4::ApproachPlayer(Strategy_Enemy *E)
{
	int tempx = (PPxPos - E->getXPos()) / (E->getSpeed() * 20+1);
	int tempy = (PPyPos - (E->getYPos()+35)) / (E->getSpeed() * 5+1);
//	int tempx = (E->getXPos()-PPxPos-640 ) / (E->getSpeed() * 20+1);
//	int tempy = (E->getYPos()-PPyPos-640 ) / (E->getSpeed() * 20+1);
	
	if (PPxPos - E->getXPos() > -180)
		Move(E,1 ,tempy);	 
	else
		Move(E,tempx ,tempy);

}

BaseBullet* Strategy4::TimetoAttack(Strategy_Enemy *E)
{
	if ( rand()%75 == 0 )	// if condition is true, attack() to generate a bullet
	{
		if (PPxPos - E->getXPos() < 0)
			return E->Attack();		
		else
			return NULL;
	}
	else
		return NULL;		
}

int Strategy4::getPlayerXPos()
{
	return PPxPos;
}

int Strategy4::getPlayerYPos()
{
	return PPyPos;
}
