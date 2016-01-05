#ifndef ConcreteBuilder2_H
#define ConcreteBuilder2_H

#include "builder.h"

class ConcreteBuilder2 : public builder
{
public:
	ConcreteBuilder2();
	virtual void buildstage1();
	virtual void buildstage2();
	virtual void buildstage3();
	virtual vector<BaseEnemy *> getstage(int);

//	virtual void setStageSequence();
};


#endif
