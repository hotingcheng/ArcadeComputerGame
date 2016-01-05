#include "Mouse.h"

Mouse::Mouse(  HWND hWnd, bool bExclusive, LPDIRECTINPUT7 DirectInput ) {

	m_pTarget = NULL;

	HRESULT hr;

	/**
	 * Create the device
	 *
	 */
	hr = DirectInput->CreateDeviceEx( GUID_SysMouse, IID_IDirectInputDevice7,
									  ( void ** ) &m_pMouseDevice, NULL );
	if( FAILED( hr )) {

		throw GameError("Couldn't create the device!\n");
	}

	/**
	 * Set the data format
	 */
	hr = m_pMouseDevice->SetDataFormat(&c_dfDIMouse);
 	if( FAILED( hr )) {

		SafeRelease( m_pMouseDevice );
		throw GameError("[cMouse::Init]: SetDataFormat failed\n");
	}

	/**
	 * Set the cooperative level
	 */
	if( bExclusive ) {

		hr = m_pMouseDevice->SetCooperativeLevel( hWnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND );
	}
	else {

		hr = m_pMouseDevice->SetCooperativeLevel( hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	if( FAILED( hr )) {

		SafeRelease( m_pMouseDevice );
		throw GameError("[cMouse::Init]: SetCooperativeLevel failed\n");
	}


	m_lastState.lX = 0;
	m_lastState.lY = 0;
	m_lastState.lZ = 0;
	m_lastState.rgbButtons[0] = 0;
	m_lastState.rgbButtons[1] = 0;
	m_lastState.rgbButtons[2] = 0;
	m_lastState.rgbButtons[3] = 0;

} // The end of Constructor

Mouse::~Mouse() {

	if( m_pMouseDevice )
	{
		m_pMouseDevice->Unacquire();
		SafeRelease( m_pMouseDevice );
	}
} // The end of Destructor


void Mouse::setReceiver( iMouseReceiver* pTarget ) {

	m_pTarget = pTarget;

} // The end of setReceiver


eResult Mouse::update()
{
	DIMOUSESTATE currState;
    HRESULT  hr; 
 
    hr = m_pMouseDevice->Poll(); 
	hr = m_pMouseDevice->GetDeviceState( sizeof(DIMOUSESTATE), (void*)&currState );

    if( FAILED(hr) ) { 

		hr = m_pMouseDevice->Acquire();
		if( FAILED( hr ) ) {

			return resFailed;
		}

	    hr = m_pMouseDevice->Poll(); 
	    hr = m_pMouseDevice->GetDeviceState( sizeof(DIMOUSESTATE),(void*)&currState ); 
		if( FAILED( hr ) ) {

			return resFailed;

		}
    } 
	if( m_pTarget ) {

		int dx = currState.lX;
		int dy = currState.lY;
		if( dx || dy ) 	{

			m_pTarget->mouseMoved( dx, dy );

		}
		if( currState.rgbButtons[0] & 0x80 ) {

			// the button got pressed.
			m_pTarget->mouseButtonDown( 0 );

		}
		if( currState.rgbButtons[1] & 0x80 ) {

			// the button got pressed.
			m_pTarget->mouseButtonDown( 1 );

		}
		if( currState.rgbButtons[2] & 0x80 ) {

			// the button got pressed.
			m_pTarget->mouseButtonDown( 2 );

		}
		if( !(currState.rgbButtons[0] & 0x80) && (m_lastState.rgbButtons[0] & 0x80) ) {

			// the button got released.
			m_pTarget->mouseButtonUp( 0 );

		}
		if( !(currState.rgbButtons[1] & 0x80) && (m_lastState.rgbButtons[1] & 0x80) ) {

			// the button got released.
			m_pTarget->mouseButtonUp( 1 );

		}
		if( !(currState.rgbButtons[2] & 0x80) && (m_lastState.rgbButtons[2] & 0x80) ) {

			// the button got released.
			m_pTarget->mouseButtonUp( 2 );

		}
	}
	m_lastState = currState;
	return resAllGood;

} // The end of Method update


eResult Mouse::acquire() {

	HRESULT hr = m_pMouseDevice->Acquire();
	if( FAILED(hr) ) {

		return resFailed;

	}
	return resAllGood;

} // The end of Method acquire

void Mouse::unAcquire() {

	m_pMouseDevice->Unacquire();

} // The end of Method unAcquire
