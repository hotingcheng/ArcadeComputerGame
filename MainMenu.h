#ifndef MAINMENU_H
#define MAINMENU_H

#include "State.h"

class MainMenu : public State {

public:
	virtual void displayMainMenu(BasePlayerPlane *);	
};

#endif
