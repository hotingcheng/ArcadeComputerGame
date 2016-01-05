#include "SoundLayer.h"

cSoundLayer* cSoundLayer::m_pGlobalSLayer = NULL;

cSoundLayer::cSoundLayer( HWND hWnd )
{
//	m_pDSound = NULL;
//	m_pPrimary = NULL;

	if( m_pGlobalSLayer )
	{
//		throw GameError( "cSoundLayer already initialized!" );
	}
	else
	{
		m_pDSound = NULL;
		m_pPrimary = NULL;

		m_pGlobalSLayer = this;

		HRESULT             hr;
		LPDIRECTSOUNDBUFFER pDSBPrimary = NULL;

		// Create IDirectSound using the primary sound device
		hr = DirectSoundCreate8( NULL, &m_pDSound, NULL );
		if( FAILED( hr ) )
		{
			throw GameError( "DirectSoundCreate failed!" );
		}

		// Set coop level to DSSCL_PRIORITY
		hr = m_pDSound->SetCooperativeLevel( hWnd, DSSCL_PRIORITY );
		if( FAILED( hr ) )
		{
			throw GameError( "SetCooperativeLevel (DS) failed!" );
		}

		// Get the primary buffer 
		sAutoZero<DSBUFFERDESC> dsbd;
		dsbd.dwFlags       = DSBCAPS_PRIMARYBUFFER;
		dsbd.dwBufferBytes = 0;
		dsbd.lpwfxFormat   = NULL;
       
		hr = m_pDSound->CreateSoundBuffer( &dsbd, &pDSBPrimary, NULL );
		if( FAILED( hr ) )
		{
			throw GameError( "CreateSoundBuffer (DS) failed!" );
		}

		// Set primary buffer format to 22kHz and 16-bit output.
		WAVEFORMATEX wfx;
		ZeroMemory( &wfx, sizeof(WAVEFORMATEX) ); 
		wfx.wFormatTag      = WAVE_FORMAT_PCM; 
		wfx.nChannels       = 2; 
		wfx.nSamplesPerSec  = 22050; 
		wfx.wBitsPerSample  = 16; 
		wfx.nBlockAlign     = wfx.wBitsPerSample / 8 * wfx.nChannels;
		wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

		if( FAILED( hr = pDSBPrimary->SetFormat(&wfx) ) )
		{
		   throw GameError( "SetFormat (DS) failed!" );
		}

	    SafeRelease( pDSBPrimary );
	}
}

cSoundLayer::~cSoundLayer()
{
	SafeRelease( m_pPrimary );
	SafeRelease( m_pDSound );
	m_pGlobalSLayer = NULL;
}
