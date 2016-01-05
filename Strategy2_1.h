#ifndef STRATEGY2_1_H
#define STRATEGY2_1_H

#include "Strategy.h"

class Strategy2_1 : public Strategy
{
private:
	// enter the distance of x/y
	virtual void Move(Strategy_Enemy *E, int xdis = -1, int ydis = 1);	

public:
	
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