#ifndef CSCREEN_H
#define CSCREEN_H

#include <windows.h>
#include <assert.h>

#include "GameError.h"
#include "DxHelper.h"
#include "CApplication.h"

class CScreen {

protected:

	// Width and height of the client area
	int m_Width, m_Height;

	// Handle to the window
	HWND m_hWnd;

	// Name of the window 
	string m_name;

	// True if the window is active	
	bool m_bActive;

	static CScreen *m_pWindow;

public:

	CScreen( 
		int width, 
		int height, 
		const char* name = "Default window name" );
	~CScreen();

	virtual LRESULT WndProc(
		HWND hWnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam );

	virtual void registerClass( WNDCLASSEX* pWc = NULL );
	virtual void initInstance();

	HWND getHWnd();
	
	bool isActive();
	
	// True -> there are messages in the queue for us to pump
	bool hasMessages();

	// res_AllGood -> continue running
	// res_False -> got a WM_QUIT.  Stop the application.
	eResult pump();

	static CScreen *getMainScreen();
	

};

inline CScreen* mainScreen()
{ 
	return CScreen::getMainScreen(); 
}

#endif 
