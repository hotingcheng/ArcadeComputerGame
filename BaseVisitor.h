#ifndef BaseVisitor_H
#define BaseVisitor_H

/*
#include "BasePlayerPlane.h"
#include "BaseEnemy.h"
#include "BaseBullet.h"
#include "Score.h"
#include "BaseTreasure.h"
#include "Strategy.h"
*/

class BasePlayerPlane;
class BaseEnemy;
class BaseBullet;
class Score;
class BaseTreasure;
class Strategy;


class BaseVisitor {

public:
	virtual void VisitPlayer(BasePlayerPlane *){};
	virtual void VisitEnemy(BaseEnemy *){};
	virtual void VisitBullet(BaseBullet *){};
	virtual void VisitScore(Score *){};
	virtual void VisitTreasure(BaseTreasure *){};
	virtual void VisitStrategy(Strategy *){};
};

#endif 
