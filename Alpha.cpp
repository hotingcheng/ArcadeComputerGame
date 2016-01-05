// Alpha.cpp: implementation of the Alpha class.
//
//////////////////////////////////////////////////////////////////////

#include "Alpha.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Alpha::Alpha(int s ,int e)
{
	start = s; 
	end = e;

	HRESULT ddrval;
	lpAlpha = NULL;
	lpAlpha = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), 
								   MAKEINTRESOURCE(IDB_ALPHA), 
								   0, 0 );

	if ( lpAlpha == NULL )
		throw GameError("Error in DDLoadBitmap of Alpha");

	// Set the ColorKey using the pixel in the top-left
	ddrval = Graphics()->DDSetColorKey( lpAlpha, CLR_INVALID );
	if ( ddrval!= DD_OK )
		throw GameError("Error in DDSetColorKey" );

}

Alpha::~Alpha()
{

}

unsigned int Alpha::getstart()
{
	return start;
}

unsigned int Alpha::getend()
{
	return end;
}

LPDIRECTDRAWSURFACE7 Alpha::getlpAlpha()
{
	return lpAlpha;
}






