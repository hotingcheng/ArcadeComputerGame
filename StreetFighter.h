#ifndef StreetFighter_H
#define StreetFighter_H

#include "CApplication.h"

#include <string>
using namespace std;

class StreetFighter : public CApplication {

public:

//	StreetFighter(PlayerFactory*);	// Constructor 
	StreetFighter();
	~StreetFighter();	// Destructor

	virtual void DoFrame( float );

	virtual void initGame();
	virtual void deleteGame();

protected:

	// Load the MainMenu bitmap to the surface
	void loadMainMenu();

	// Load the BackGround bitmap to the surface
	void loadBackGround();

	// This private method is called to display the Main Menu
	void displayMainMenu();

	// This private method is called to diaplay the Game BackGround
	void displayBackGround();

	LPDIRECTDRAWSURFACE7 lpDDMainMenu;
	LPDIRECTDRAWSURFACE7 lpDDBackGround;

};

#endif