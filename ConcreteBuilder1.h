#ifndef ConcreteBuilder1_H
#define ConcreteBuilder1_H

#include "builder.h"

class ConcreteBuilder1 : public builder
{
public:
	ConcreteBuilder1();
	virtual void buildstage1();
	virtual void buildstage2();
	virtual void buildstage3();
	virtual vector<BaseEnemy *> getstage(int);

//	virtual void setStageSequence();
};


#endif
