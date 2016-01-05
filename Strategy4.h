#ifndef STRATEGY4_H
#define STRATEGY4_H

#include "Strategy.h"

class Strategy4 : public Strategy
{
private:
	// enter the distance of x/y
	virtual void Move(Strategy_Enemy *E, int xdis = 0, int ydis = 0);	
	
public:
	
	// track player plane position
	virtual void TrackPlayerPosition(BasePlayerPlane *PP); 	
	
	// after tracking , approach player plane
	virtual void ApproachPlayer(Strategy_Enemy *E);

	// if condition is true, invoke enemy to attack/generate a bullet
	virtual BaseBullet* TimetoAttack(Strategy_Enemy *E);	

	virtual int getPlayerXPos();
	virtual int getPlayerYPos();
};



#endif