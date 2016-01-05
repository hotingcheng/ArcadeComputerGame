#ifndef MOUSE_H
#define MOUSE_H

#ifndef DIRECTINPUT_VERSION 
#define DIRECTINPUT_VERSION 0x0700
#endif

#include <dinput.h>
#include "GameError.h"
#include "DxHelper.h"

 
// Any Class that implements this interface can receive input from the mouse.
struct iMouseReceiver {

	virtual void mouseMoved( int dx, int dy ) {};
	virtual void mouseButtonUp( int button ) {};
	virtual void mouseButtonDown( int button ) {};

}; // The end of Interface iMouseReceiver

class Mouse {

	LPDIRECTINPUTDEVICE7	m_pMouseDevice; 

	DIMOUSESTATE			m_lastState;

	iMouseReceiver*			m_pTarget;

public:

	Mouse( HWND hWnd, bool bExclusive, LPDIRECTINPUT7 );
	~Mouse();

	/**
	 * Use this to establish a MouseReceiver as the current 
	 * input focus
	 */
	void setReceiver( iMouseReceiver* pTarget );

	eResult update();

	eResult acquire();
	void unAcquire();

}; // The end of Class Mouse

#endif 
