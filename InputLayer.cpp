#include "InputLayer.h"
#include "CApplication.h"
#include "CScreen.h"

InputLayer* InputLayer::m_pInputLayer = NULL;

InputLayer::InputLayer( 
	HINSTANCE hInst, 
	HWND hWnd, 
	bool bExclusive, 
	bool bUseKeyboard, 
	bool bUseMouse )
{


//	m_pKeyboard = NULL;
//	m_pMouse = NULL;

	if( m_pInputLayer ) {

//		throw GameError("InputLayer already initialized!\n");
	}
	else
	{
		m_pKeyboard = NULL;
		m_pMouse = NULL;

		m_pInputLayer = this;

		HRESULT hr;

		
		// Create the DirectInput7 COM object
		hr = DirectInputCreateEx( hInst, DIRECTINPUT_VERSION, IID_IDirectInput7,
							   ( void ** )&m_pDirectInput, NULL );
		if( FAILED(hr) ) {

			throw GameError("DirectInput7 object could not be created\n"); 
		}

		try {

			if( bUseKeyboard ) {

				m_pKeyboard = new Keyboard( hWnd, m_pDirectInput );
			}
			if( bUseMouse ) {

				m_pMouse = new Mouse( hWnd, bExclusive, m_pDirectInput );
			}
		}
		catch( ... ) {

			SafeRelease( m_pDirectInput );
			throw;
		}
	}
} // The end of Constructor

InputLayer::~InputLayer() {

	if( m_pDirectInput ) {

		if( m_pKeyboard ) {

			delete m_pKeyboard; // this does all the de-init.
			m_pKeyboard = NULL;
		}

		if( m_pMouse ) {

			delete m_pMouse; // this does all the de-init.
			m_pMouse = NULL;
		}
		SafeRelease( m_pDirectInput );
	}
	m_pInputLayer = NULL;

} // The end of Destructor

void InputLayer::updateDevices() {

	if( m_pKeyboard ) {

		m_pKeyboard->update();
	}
	if( m_pMouse ) {

		m_pMouse->update();
	}

} // The end of Method updateDevices

void InputLayer::setFocus() {

	if( m_pKeyboard ) {

		m_pKeyboard->clearTable();
	}
	if( m_pMouse ) {

		m_pMouse->acquire();
	}
} // The end of Method setFocus

void InputLayer::killFocus() {

	if( m_pKeyboard ) {

		m_pKeyboard->clearTable();

	}
	if( m_pMouse ) {

		m_pMouse->unAcquire();
	}
} // The end of Method killFocus

void InputLayer::create( HINSTANCE hInst, HWND hWnd, bool bExclusive, 
			 bool bUseKeyboard, bool bUseMouse )
{
	// everything is taken care of in the constructor
	new InputLayer( hInst, hWnd, bExclusive, bUseKeyboard, bUseMouse );

} // The end of Method create

Keyboard* InputLayer::getKeyboard() { return m_pKeyboard; }
// The end of Method getKeyboard

Mouse* InputLayer::getMouse() { return m_pMouse; }
// The end of Method getMouse

InputLayer* InputLayer::getInputLayer() { return m_pInputLayer; }
// The end of Method getInputLayer

LPDIRECTINPUT7 InputLayer::getDirectInput() { return m_pDirectInput; }
// The end of Method getDirectInput
