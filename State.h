#ifndef STATE_H
#define STATE_H

#include "GraphicsLayer.h"

class State {

public:
	virtual void displayMainMenu(BasePlayerPlane *){};
	virtual void displayGame(){};
	virtual void displayRaiseLevel(){};
	virtual void displayGameOver(){};
	virtual void endGame(){};
};

#endif
