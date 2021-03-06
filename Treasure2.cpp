#include "Treasure2.h"
/*
Treasure2::Treasure2(Treasure2& T)
{
	Destroy = 0;
	xPos = 0;
	yPos = 0;
	lpDDNormal = T.lpDDNormal;
}
*/
Treasure2::Treasure2() {

	xPos = 0;
	yPos = 0;
	frame = 0;
	iType = 2;
	rcLastPos.left   = 0;
	rcLastPos.top    = 0;
	rcLastPos.right  = 0;
	rcLastPos.bottom = 0;

	// Create the surface from bitmap
	HRESULT				ddrval;
	lpDDNormal = NULL;
	lpDDNormal = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), 
								   MAKEINTRESOURCE(IDB_treasure2), 
								   0, 0 );

	if ( lpDDNormal == NULL )
		throw GameError("Error in DDLoadBitmap of Treasure2");

	// Set the ColorKey using the pixel in the top-left
	ddrval = Graphics()->DDSetColorKey( lpDDNormal, CLR_INVALID );
	if ( ddrval!= DD_OK )
		throw GameError("Error in DDSetColorKey" );

//	ddrval = Graphics()->DDCopyBitmap(lpDDNormal, hbm, 0, 0, 500, 125 );

} // The end of Constructor

Treasure2::~Treasure2() {

	SafeRelease ( lpDDNormal );	

} // The end of Destructor

int Treasure2::getType() const {

	return iType;

} // The end of Method getType

const void Treasure2::setType(int iNewType) {

	iType = iNewType;

} // The end of Method setType

int Treasure2::getXPos() const {

	return xPos;

} // The end of Method getX

int Treasure2::getYPos() const {

	return yPos;

} // The end of Method getYPos

const void Treasure2::move(int Qtde) {

	rcLastPos.left   = xPos;
	rcLastPos.top    = yPos;
	rcLastPos.right  = xPos + 25;
	rcLastPos.bottom = yPos + 25;
	if (rcLastPos.left < 0)
		rcLastPos.left = 0;
	xPos -= Qtde;
	

} // The end of Method move

const void Treasure2::setXY(const int nx, const int ny) {

	Destroy = 0;
	rcLastPos.left   = nx;
	rcLastPos.top    = ny;
	rcLastPos.right  = nx + 25;
	rcLastPos.bottom = ny + 25;
	xPos = nx;
	yPos = ny;
	

} // The end of setXY


bool Treasure2::draw(LPDIRECTDRAWSURFACE7 lpDest )  {

	RECT		srcRect;

	HRESULT		hRet;
//	int			iClipTop;
//	int			iClipBottom;

	move(2);

	srcRect.left = frame * 25;
	srcRect.top = 0;// + iClipTop;
	srcRect.right = frame * 25 + 25;
	srcRect.bottom = 25;// - iClipBottom;

	frame++;

	checkBoundary();

	hRet = lpDest->BltFast( xPos, yPos, lpDDNormal, &srcRect, TRUE);

//	if ( hRet!= DD_OK )
//		throw GameError("Error in DDSetColorKey" );		

	if (frame == 19)
		frame = 0;

	return TRUE;
}


void Treasure2::setDestroy()
{
	Destroy = 1;
}

int Treasure2::getDestroy()
{
	return Destroy;
}


const void Treasure2::checkBoundary() {

	if ( xPos < 10 )
	{
		Destroy = 1;
		xPos = 10;
	}

	if ( yPos > 455 )
	{		
		yPos = 455;
//		state = 2;
	}
	if ( yPos < 0 )
	{
		yPos = 0;
//		state = 2;
	}

} // The end of Method checkBoundary