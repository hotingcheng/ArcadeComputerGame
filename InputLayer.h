#ifndef INPUTLAYER_H
#define INPUTLAYER_H

#pragma warning( disable : 4786 )

#include "Keyboard.h"
#include "Mouse.h"

class InputLayer {

private:

	Keyboard*		m_pKeyboard;	// Pointer to the Class Keyboard	 
	Mouse*			m_pMouse;	    // Pointer to the Class Mouse 

	// The DirectInput7 COM object
	LPDIRECTINPUT7	m_pDirectInput; // Pointer to the DirectInput8 Object
	
	static InputLayer* m_pInputLayer; // Pointer to the InputLayer

	InputLayer( HINSTANCE hInst, HWND hWnd, bool bExclusive, bool bUseKeyboard, 
				bool bUseMouse );

public:

	virtual ~InputLayer();

	Keyboard* getKeyboard();
	Mouse* getMouse();
	static InputLayer* getInputLayer();

	void updateDevices();

	LPDIRECTINPUT7 getDirectInput();
	
	void setFocus(); // called when the app gains focus
	void killFocus(); // called when the app must release focus

	static void create( HINSTANCE, HWND, bool, bool= true, bool = false );

};

inline InputLayer* Input()
{
	return InputLayer::getInputLayer();
}

#endif 
