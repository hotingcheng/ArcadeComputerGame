#include "CScreen.h"

using namespace std;

CScreen* CScreen::m_pWindow = NULL;

GameError* g_pThrownError = NULL;


LRESULT CALLBACK GlobalWndProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam )
{
	assert( mainScreen() );

	return mainScreen()->WndProc( hWnd, uMsg, wParam, lParam );
}

CScreen::CScreen( int width, int height, const char* name ) :
	m_Width( width ),
	m_Height( height ),
	m_hWnd( NULL )
{
	/**
	 * Only one primary window should be created.
	 */
	if( m_pWindow )
	{
//		throw GameError( "Screen is already instantiated!" );
	}
	else
		{
		m_pWindow = this;
		m_bActive = false;

		// copy the name over
		m_name = string( name );
	}
}

CScreen::~CScreen()
{
	DestroyWindow( m_hWnd );
	m_pWindow = NULL;
}


LRESULT CScreen::WndProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam )
{
	
	if( g_pThrownError )
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);	
	}


	bool bRunDefault = false;

	try
	{
		switch( uMsg ) 
		{
		case WM_CREATE:
			{
				mainScreen()->m_hWnd = hWnd;
				mainScreen()->m_bActive = true;
				break;
			}
		case WM_PAINT:
			{
				// don't do anything.
				ValidateRect( hWnd, NULL );
				break;
			}
		case WM_KEYDOWN:
			{
				switch( wParam )
				{
				// Quit if the escape key is pressed
				case VK_ESCAPE:
					{
						//PostQuitMessage(0);
						break;
					}
				default:
					{
						break;
					}
				}
			}

		case WM_SETFOCUS:
			{
			
				if( Input() )
				{
					Input()->setFocus();
				}
				break;
			
			}
		case WM_KILLFOCUS:
			{
			
				if( Input() )
				{
					Input()->killFocus();
				}
				break;
			
			}
		case WM_ERASEBKGND:
			{
				break;
			}
		case WM_DESTROY:
			{
				//PostQuitMessage(0);
				break;
			}
		default:
			bRunDefault = true;
			break;
		}	
	}
	catch( GameError& err ) {

		g_pThrownError = new GameError( err );
		return 0;
	}

	if( bRunDefault ) {

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}


void CScreen::registerClass( WNDCLASSEX* pWc )
{
	WNDCLASSEX wcex;
	if( pWc )
	{
		wcex = *pWc;
	}
	else
	{
		// fill in some default values
		wcex.cbSize = sizeof(WNDCLASSEX); 

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= GlobalWndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= AppInstance();
		wcex.hIcon			= 0;
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= 0;
		wcex.lpszClassName	= m_name.c_str();
		wcex.hIconSm		= 0;
	}

	if( 0 == RegisterClassEx(&wcex) )
	{
		throw GameError("[cWindow::RegisterClass]: Registering window class failed!");
	}
}

bool CScreen::hasMessages()
{
	MSG msg;
    if( 0 == PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE ) )
	{
		// There weren't any messages
		return false;
	}
	return true;
}

eResult CScreen::pump()
{
	MSG msg;
	PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );

	if( WM_QUIT == msg.message )
		return resFalse;

	TranslateMessage( &msg );
    DispatchMessage( &msg );

	/**
	 * Check to see if an error occured inside the pump
	 */
	if( g_pThrownError )
	{
		GameError out = *g_pThrownError;
		delete g_pThrownError;
		throw out;
	}


	return resAllGood;
}

void CScreen::initInstance()
{
	CreateWindow( 
	   m_name.c_str(), 
	   m_name.c_str(), 
	   WS_POPUP,
	   0, 0, m_Width, m_Height, 
	   NULL, 
	   NULL, 
	   AppInstance(), 
	   NULL);

   if ( !m_hWnd )
   {
		throw GameError("[cWindow::InitInstance]: Creating window failed!\n");
   }
   UpdateWindow( m_hWnd );
}

HWND CScreen::getHWnd() { return m_hWnd; }
// The end of Method getHWnd

bool CScreen::isActive() { return m_bActive; }
// The end of Method isActive

CScreen *CScreen::getMainScreen() { return m_pWindow; }
