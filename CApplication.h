#ifndef APPLICATION_H
#define APPLICATION_H

#include <cppunit/ui/text/TestRunner.h>
#include "StdHeader.h"
#include "TestPlayer.h"

using namespace CppUnit;
using namespace TextUi;

class CApplication {

protected:

	string	m_title; // Name the window should have
	int		m_width; // Width of our application
	int		m_height; // Height of our application
	int		m_bpp; // Desired depth (may not be possible)

	bool	m_bActive; // Is the appliation active?

	unsigned int m_glFlags; // Flags for the graphics layer

	static CApplication *m_pCApp; // The static pointer to this class


public:

	// Constructor and Destructor
	CApplication();
	~CApplication();
//	virtual ~CApplication();

	
	// Init the application. It call the below four init functions in order
	virtual void init(); 

	// Init the Screen
	virtual void initScreen();

	// Init the graphical Layer
	virtual void initGraphics();

	// Init the Input Layer
	virtual void initInput();

	// Init the Sound Layer and CSound class
	virtual void initSound();

	// Test the game by using Cpp Unit
	virtual void testGame();

	// Init the object used in Game e.g. character, enemy
	virtual void initGame();

	// Free all the resource allocated in the function initGame
	virtual void deleteGame();
	
	// Run the Applcation
	virtual void run();

	
	// Handles all code that should be run each frame. 
	// All the game logic should be done here
	// timeDelta == amount of time (in seconds) since last call
	virtual void DoFrame( float timeDelta );
	virtual void DoIdleFrame( float timeDelta );
	
	// Method return the pointer of this CApplication
	static CApplication* getApplication() { return m_pCApp; }

	// Explicitly terminate this applicaion
	static void killApplication() 
	{
		delete m_pCApp;
		m_pCApp = NULL;
	}
};

inline CApplication* Application()
{
	return CApplication::getApplication();
}

HINSTANCE AppInstance();

// returns a ptr to a valid application object
CApplication *createCApplication(); 

#endif 
