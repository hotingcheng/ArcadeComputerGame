#include "Keyboard.h"

Keyboard::Keyboard( HWND hWnd, LPDIRECTINPUT7 DirectInput ) {

	m_pTarget = NULL;
	
	HRESULT hr;

	
	// Create the keyboard device
	hr = DirectInput->CreateDeviceEx( GUID_SysKeyboard, IID_IDirectInputDevice7,
									  ( void** )&m_pKeyboardDevice, NULL );
    if( FAILED(hr) ) { 

        throw GameError("Keyboard could not be created\n");
    }  
	
	// Set the keyboard data format
	hr = m_pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard); 
    if( FAILED(hr) ) { 

		SafeRelease( m_pKeyboardDevice );
        throw GameError("Keyboard could not be created\n");
    } 
 
    
	// Set the cooperative level 
	hr = m_pKeyboardDevice->SetCooperativeLevel(
		hWnd,
		DISCL_BACKGROUND  | DISCL_NONEXCLUSIVE); 
    if( FAILED(hr) ) { 

		SafeRelease( m_pKeyboardDevice );
        throw GameError("Keyboard coop level could not be changed\n");
    } 

	memset( m_keyState, 0, 256*sizeof(bool) );	

} // The end of Constructor

Keyboard::~Keyboard() {

	if( m_pKeyboardDevice ) {

		m_pKeyboardDevice->Unacquire();
		SafeRelease( m_pKeyboardDevice );
	}

} // The end of Destructor

void Keyboard::setReceiver( iKeyboardReceiver* pTarget ) {

	// Set the new target.
	m_pTarget = pTarget;

} // The end of Method setReceiver

bool Keyboard::poll( int key ) {

	// stuff goes in here.
	if( m_keyState[key] & 0x80 )
		return true;
	return false;

} // The end of Method poll

eResult Keyboard::update() {

	char     newState[256]; 
    HRESULT  hr; 
 
    hr = m_pKeyboardDevice->Poll(); 
    hr = m_pKeyboardDevice->GetDeviceState(sizeof(newState),(LPVOID)&newState); 

    if( FAILED(hr) ) { 

		hr = m_pKeyboardDevice->Acquire();
		if( FAILED( hr ) ) {

			return resFailed;

		}

	    hr = m_pKeyboardDevice->Poll(); 
	    hr = m_pKeyboardDevice->GetDeviceState(sizeof(newState),(LPVOID)&newState); 
		if( FAILED( hr ) ) {

			return resFailed;

		}
    } 


	if( m_pTarget ) {

		int i;
		for( i=0; i< 256; i++ ) {

			if( m_keyState[i] != newState[i] ) {

				// Something happened to this key since the last time we checked
				if( !(newState[i] & 0x80) ) {

					// It was Released
					m_pTarget->keyRelease( i );
				}
				else {

					// Do nothing; it was just pressed, it'll get a keydown 
					// in a bit, and we dont' want to send the signal to the 
					// input target twice
				}
			}

			// copy the state over (we could do a memcpy at the end, but this
			// will have better cache performance)
			m_keyState[i] = newState[i];

			if( poll( i ) ) {

				// It was pressed
				m_pTarget->keyPresse( i );
			}
		}
	}
	else {

		// copy the new states over.
		memcpy( m_keyState, newState, 256 );
	}
 
	return resAllGood;

} // The end of Method update

void Keyboard::clearTable() {

		memset( m_keyState, 0, sizeof(char)*256 );

} // The end of clearTable	
