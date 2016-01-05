#ifndef STRATEGY_H
#define STRATEGY_H

#include "Strategy_Enemy.h"
#include <stdlib.h>
#include <time.h>
#include "BaseBullet.h"

#include "BaseVisitor.h"

//class BaseEnemy;
class BasePlayerPlane;

class Strategy 
{
//	friend class BaseEnemy;
protected:
	int PPxPos;		// player's current position
	int PPyPos;

		// enter the distance of x/y
	virtual void Move(Strategy_Enemy *E, int xdis=-1, int ydis=0)=0;

public:

//	virtual void Move(int xdis, int ydis);
	
	// track player plane position
	virtual void TrackPlayerPosition(BasePlayerPlane *PP)=0;
	
	// after tracking , approach player plane
	virtual void ApproachPlayer(Strategy_Enemy *E)=0;
	
	// if condition is true, invoke enemy to attack/generate a bullet
	virtual BaseBullet* TimetoAttack(Strategy_Enemy *E)=0;

	virtual int getPlayerXPos()=0;
	virtual int getPlayerYPos()=0;

	virtual void Accept(BaseVisitor &v){ v.VisitStrategy(this); };
};



#endif