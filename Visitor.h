#ifndef Visitor_H
#define Visitor_H

#include "BaseVisitor.h"

class Visitor : public BaseVisitor
{

public:
	virtual void VisitPlayer(BasePlayerPlane *);
	virtual void VisitEnemy(BaseEnemy *);
	virtual void VisitBullet(BaseBullet *);
	virtual void VisitScore(Score *);
	virtual void VisitTreasure(BaseTreasure *);
	virtual void VisitStrategy(Strategy *);

};

#endif 
