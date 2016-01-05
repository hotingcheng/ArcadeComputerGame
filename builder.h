#ifndef BUILDER_H
#define BUILDER_H

#include "BaseEnemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy4_2.h"
#include "Leader1.h"
#include "Leader2.h"
#include "BigBoss1.h"

class builder
{
protected:
	vector<BaseEnemy *> EnemyContainer;
public:
	builder(){};
	virtual void buildstage1(){};
	virtual void buildstage2(){};
	virtual void buildstage3(){};
	virtual void buildstage4(){};
	virtual void buildstage5(){};
	virtual void buildstage6(){};
	virtual void buildstage7(){};
	virtual void buildstage8(){};
	virtual void buildstage9(){};
	virtual void buildstage10(){};
	
	virtual vector<BaseEnemy *> getstage(int){return NULL;};
/*	virtual vector<BaseEnemy *> getstage2(){return NULL;};
	virtual vector<BaseEnemy *> getstage3(){return NULL;};
	virtual vector<BaseEnemy *> getstage4(){return NULL;};
	virtual vector<BaseEnemy *> getstage5(){return NULL;};
	virtual vector<BaseEnemy *> getstage6(){return NULL;};
	virtual vector<BaseEnemy *> getstage7(){return NULL;};
	virtual vector<BaseEnemy *> getstage8(){return NULL;};
	virtual vector<BaseEnemy *> getstage9(){return NULL;};
	virtual vector<BaseEnemy *> getstage10(){return NULL;};
*/
//	virtual void setStageSequence(){};
};


#endif
