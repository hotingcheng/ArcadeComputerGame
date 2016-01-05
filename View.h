#ifndef View_H
#define View_H

#include "StarWar.h"

class View : public StarWar
{
	virtual void ViewAll();
	virtual void ViewPlayer(BasePlayerPlane *);
	virtual void ViewEnemy();
	virtual void ViewBullet();
	virtual void ViewTreasure();

};

#endif
