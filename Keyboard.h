#ifndef KEYBOARD_H
#define KEYBOARD_H

#ifndef DIRECTINPUT_VERSION 
#define DIRECTINPUT_VERSION 0x0700
#endif

#include <dinput.h>
#include "GameError.h"
#include "DxHelper.h"

//Any Class that implements this interface can receive input from the keyboard.
struct iKeyboardReceiver
{
	virtual void keyRelease( int key ) {};
	virtual void keyPresse( int key ) {};

}; // The end of Interface iKeyboardReceiver


class Keyboard {

	LPDIRECTINPUTDEVICE7	m_pKeyboardDevice;	// The Pointer to the DirectInput device keyboard
	
	char					m_keyState[256];	// The char array to store the state of the Device keyboard 

	iKeyboardReceiver*		m_pTarget;			// Pointer to the Receiver

public:

	Keyboard( HWND, LPDIRECTINPUT7 );
	~Keyboard();

	void clearTable();

	// Poll to see if a certain key is down
	bool poll( int );

	// Use this to establish a KeyboardReceiver as the current input focus
	void setReceiver( iKeyboardReceiver* );

	// Notify the Receiver if a key is pressed and release, ie keyRelease and
	// keyPressed is called
	eResult update();

}; // The end of Class Keyboard

#endif 
