#ifndef STRATEGY1_H
#define STRATEGY1_H

#include "Strategy.h"

class Strategy1 : public Strategy
{
private:
	int movex;
	int movey;

	// enter the distance of x/y
	virtual void Move(Strategy_Enemy *E, int xdis = -2, int ydis = 0);	


public:
	Strategy1(int,int);
	
	// track player plane position
	virtual void TrackPlayerPosition(BasePlayerPlane *PP); 	
	
	// after tracking , approach player plane
	virtual void ApproachPlayer(Strategy_Enemy *E);

	// if condition is true, invoke enemy to attack/generate a bullet
	virtual BaseBullet* TimetoAttack(Strategy_Enemy *E);	
	
	virtual int getPlayerXPos(){return 0;};
	virtual int getPlayerYPos(){return 0;};
};



#endif