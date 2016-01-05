#include "Treasure1.h"
/*
Treasure1::Treasure1(Treasure1& T)
{
	Destroy = 0;
	xPos = 0;
	yPos = 0;
	lpDDNormal = T.lpDDNormal;
}
*/
Treasure1::Treasure1() {

	Destroy = 0;
	xPos = 0;
	yPos = 0;
	frame = 0;
	iType = 1;
	rcLastPos.left   = 0;
	rcLastPos.top    = 0;
	rcLastPos.right  = 0;
	rcLastPos.bottom = 0;

	// Create the surface from bitmap
	HRESULT				ddrval;
	lpDDNormal = NULL;
	lpDDNormal = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), 
								   MAKEINTRESOURCE(IDB_treasure1), 
								   0, 0 );

	if ( lpDDNormal == NULL )
		throw GameError("Error in DDLoadBitmap of Treasure1");

	// Set the ColorKey using the pixel in the top-left
	ddrval = Graphics()->DDSetColorKey( lpDDNormal, CLR_INVALID );
	if ( ddrval!= DD_OK )
		throw GameError("Error in DDSetColorKey" );

//	ddrval = Graphics()->DDCopyBitmap(lpDDNormal, hbm, 0, 0, 500, 125 );

} // The end of Constructor

Treasure1::~Treasure1() {

	SafeRelease ( lpDDNormal );	

} // The end of Destructor

int Treasure1::getType() const {

	return iType;

} // The end of Method getType

const void Treasure1::setType(int iNewType) {

	iType = iNewType;

} // The end of Method setType

int Treasure1::getXPos() const {

	return xPos;

} // The end of Method getX

int Treasure1::getYPos() const {

	return yPos;

} // The end of Method getYPos

const void Treasure1::move(int Qtde) {

/*	rcLastPos.left   = xPos;
	rcLastPos.top    = yPos;
	rcLastPos.right  = xPos + 25;
	rcLastPos.bottom = yPos + 25;
	if (rcLastPos.left < 0)
		rcLastPos.left = 0;
*/	xPos -= Qtde;
	

} // The end of Method move

const void Treasure1::setXY(const int nx, const int ny) {

	
	rcLastPos.left   = nx;
	rcLastPos.top    = ny;
	rcLastPos.right  = nx + 25;
	rcLastPos.bottom = ny + 25;
	xPos = nx;
	yPos = ny;
	

} // The end of setXY


bool Treasure1::draw(LPDIRECTDRAWSURFACE7 lpDest )  {

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
	
	if (frame == 19)
		frame = 0;

	return TRUE;
}

void Treasure1::setDestroy()
{
	Destroy = 1;
}

int Treasure1::getDestroy()
{
	return Destroy;
}

const void Treasure1::checkBoundary() {

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