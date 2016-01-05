#include "CApplication.h"


#include <mmsystem.h> // for timeGetTime

CApplication* CApplication::m_pCApp = NULL;

HINSTANCE g_hInstance;

HINSTANCE AppInstance() {
	return g_hInstance;
}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	
	CApplication* pCApp;

	g_hInstance = hInstance;

	try { 

		pCApp = createCApplication();

		pCApp->init();
		pCApp->run();

	}
	catch( GameError& err ) {
		
		/*
		if( Graphics() )
		{
			Graphics()->DestroyAll();
		}
		MessageBox( NULL, err.GetText(), "Error!", MB_OK|MB_ICONEXCLAMATION );
		*/
		// Clean everything up
//		MessageBox( NULL, err.getText().c_str(), "Error!", MB_OK|MB_ICONEXCLAMATION );
		delete pCApp;
		return 0;
	}

	delete pCApp;
	return 0;

} // The end of Method WinMain

CApplication::CApplication() {

	if( m_pCApp ) {

//		throw GameError("Application object already created!\n");
	}
	else
	{
		m_pCApp = this;

		m_title = string( "IEG3080 Game Project Star War" );
		m_width = screenWidth;
		m_height = screenHeight;
		m_bpp = colorBit;
		m_bActive = true;
	}
} // The end of Constructor

CApplication::~CApplication() {

//	deleteGame();
	delete Graphics();
	delete Input();
	delete Sound();
	delete mainScreen();

//	int i;

//	i =0;

} // The end of Destructor


void CApplication::init() {

	initScreen();
	initGraphics();
	initInput();
	initSound();
	testGame();
	initGame();
	
} // The end of Method init


void CApplication::run() {

	bool done = false;

	static float lastTime = (float)timeGetTime(); 

	// While loop to loop "die" the game 
	while( !done ) {

		/**
		 * Does the user want to quit?
		 */
	/*	if( Input()->GetKeyboard() )
		{
			if( Input()->GetKeyboard()->Poll( DIK_ESCAPE ) ||
				Input()->GetKeyboard()->Poll( DIK_Q ) )
			{
				PostMessage( MainWindow()->GetHWnd(), WM_CLOSE, 0, 0 );
			}
		}*/


		// While loop to pump and process the message
		while( !done && mainScreen()->hasMessages() ) {

			if( resFalse == mainScreen()->pump() )
				done = true;
		}


		/**
		 * We're about ready to let the class draw the frame.
		 * find out how much time elapsed since the last frame
		 * we calc these whether we have focus or not, to avoid
		 * a large delta once we start rendering after idle time
		 */
		float currTime = (float)timeGetTime();
		float delta = (currTime - lastTime)/1000.f;

		if( m_bActive ) {

			// Update the Input devices
			if( Input() )
				Input()->updateDevices();

			DoFrame( delta );
		}
		else {

			DoIdleFrame( delta );
		}

		lastTime = currTime;
	}

} // The end of Method run


// Empty Method, no implementation, to be overidde by subclass
void CApplication::DoFrame( float timeDelta ) {
}

// Empty Method, no implementation
void CApplication::DoIdleFrame( float timeDelta ) {
}

void CApplication::initScreen() {

	new CScreen( m_width, m_height, m_title.c_str() );

	mainScreen()->registerClass();
	mainScreen()->initInstance();

} // The end of Method initScreen


void CApplication::initGraphics() {

	GraphicsLayer::create( mainScreen()->getHWnd(), m_width, m_height, NULL );
		
} // The end of Method initGraphics

void CApplication::initInput() {

	InputLayer::create( AppInstance(), mainScreen()->getHWnd(), NULL, true, true );

} // The end of Method initInput

void CApplication::initSound() {

	cSoundLayer::Create( mainScreen()->getHWnd() );
	
	
} // The end of Method initSound

void CApplication::testGame() {

	CppUnit::TextUi::TestRunner runner;
	runner.addTest( TestPlayer::suite() );
	runner.run();

} // The end of Method testGame

void CApplication::initGame() { } 
// The end of Method initGame

void CApplication::deleteGame() { } 
// The end of Method deleteGame

