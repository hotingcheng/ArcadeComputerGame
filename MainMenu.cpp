#include "MainMenu.h"

void MainMenu::displayMainMenu(BasePlayerPlane *pp)
{
	HRESULT ddrval;

	ddrval = Graphics()->getBackBuffer()->BltFast( 0, 0, lpDDMainMenu, NULL, FALSE  );
	ddrval = Graphics()->getBackBuffer()->BltFast( 210, 333, lpDDCursor, NULL, TRUE);

	if ( Input()->getKeyboard()->poll( DIK_RETURN ) ) 
	{
		HRESULT ddrval = Graphics()->getBackBuffer()->BltFast( 0, 0, lpDDBackGround, NULL, FALSE );
		pp->setXY(70,200);
		pp->setstate(0);
		gameState = 2;
		timer.Start();
	};	

}