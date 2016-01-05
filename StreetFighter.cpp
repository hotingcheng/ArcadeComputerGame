#include "StreetFighter.h"
//#include "CreateGame.h"

StreetFighter::StreetFighter()
{
}

StreetFighter::~StreetFighter()
{
	deleteGame();
}

void StreetFighter::loadBackGround() {

	lpDDBackGround = NULL;
	lpDDBackGround = Graphics()->DDLoadBitmap( Graphics()->getDirectDraw(), 
										MAKEINTRESOURCE(IDB_BACKGROUND), 
										0, 0 );

	if ( lpDDBackGround == NULL )
		throw GameError(" Error in loadBitmap of BackGround");
		
} // The end of Method loadBackGround

void StreetFighter::loadMainMenu()
{
	lpDDMainMenu = NULL;
	lpDDMainMenu = Graphics()->DDLoadBitmap( Graphics()->getDirectDraw(), 
											MAKEINTRESOURCE(IDB_test), 
											0, 0 );

	if ( lpDDMainMenu == NULL )
		throw GameError(" Error in loadBitmap of MainMenu");
}

void StreetFighter::displayMainMenu()
{
	HRESULT ddrval;
	ddrval = Graphics()->getBackBuffer()->BltFast( 0, 0, lpDDMainMenu, NULL, FALSE  );
}

void StreetFighter::DoFrame(float timedelta)
{
	displayMainMenu();
	Graphics()->flip();
}

void StreetFighter::initGame()
{
	loadBackGround();
	loadMainMenu();
}

void StreetFighter::deleteGame()
{
	SafeRelease(lpDDMainMenu);
	SafeRelease(lpDDBackGround);
}