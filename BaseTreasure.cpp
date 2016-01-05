#include "BaseTreasure.h"

BaseTreasure::BaseTreasure() {

	xPos = 0;
	yPos = 0;
	pNext = NULL;
	pPrev = NULL;
	frame = 0;
	iType = 0;
	rcLastPos.left   = 0;
	rcLastPos.top    = 0;
	rcLastPos.right  = 0;
	rcLastPos.bottom = 0;

	// Create the surface from bitmap
	HRESULT				ddrval;
	lpDDNormal = NULL;
	lpDDNormal = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), 
								   MAKEINTRESOURCE(IDB_BaseTreasure), 
								   0, 0 );

	if ( lpDDNormal == NULL )
		throw GameError("Error in DDLoadBitmap of BaseTreasure");

	// Set the ColorKey using the pixel in the top-left
	ddrval = Graphics()->DDSetColorKey( lpDDNormal, CLR_INVALID );
	if ( ddrval!= DD_OK )
		throw GameError("Error in DDSetColorKey" );

//	ddrval = Graphics()->DDCopyBitmap(lpDDNormal, hbm, 0, 0, 500, 125 );

} // The end of Constructor

BaseTreasure::~BaseTreasure() {

	SafeRelease ( lpDDNormal );	

} // The end of Destructor

int BaseTreasure::getType() const {

	return iType;

} // The end of Method getType

const void BaseTreasure::setType(int iNewType) {

	iType = iNewType;

} // The end of Method setType

int BaseTreasure::getXPos() const {

	return xPos;

} // The end of Method getX

int BaseTreasure::getYPos() const {

	return yPos;

} // The end of Method getYPos

const void BaseTreasure::move(int Qtde) {

	rcLastPos.left   = xPos;
	rcLastPos.top    = yPos;
	rcLastPos.right  = xPos + 25;
	rcLastPos.bottom = yPos + 25;
	if (rcLastPos.left < 0)
		rcLastPos.left = 0;
	xPos -= Qtde;
	

} // The end of Method move

const void BaseTreasure::setXY(const int nx, const int ny) {

	
	rcLastPos.left   = nx;
	rcLastPos.top    = ny;
	rcLastPos.right  = nx + 25;
	rcLastPos.bottom = ny + 25;
	xPos = nx;
	yPos = ny;
	

} // The end of setXY


bool BaseTreasure::draw(LPDIRECTDRAWSURFACE7 lpDest )  {

	RECT		srcRect;

	HRESULT		hRet;
//	int			iClipTop;
//	int			iClipBottom;

	srcRect.left = frame * 25;
	srcRect.top = ((iType - 1) * 25);// + iClipTop;
	srcRect.right = frame * 25 + 25;
	srcRect.bottom = ((iType - 1) * 25) + 25;// - iClipBottom;

	frame++;

	hRet = lpDest->BltFast( xPos, yPos, lpDDNormal, &srcRect, TRUE);
	
	/*
	if (yPos < 0)
		iClipTop = yPos * -1;
	else
		iClipTop = 0;

	if (yPos+25 > 455)
		iClipBottom = yPos+25-455;
	else
		iClipBottom = 0;

	rcRect.left = frame * 25;
	rcRect.top = ((iType - 1) * 25) + iClipTop;
	rcRect.right = frame * 25 + 25;
	rcRect.bottom = ((iType - 1) * 25) + 25 - iClipBottom;

	frame++;
*/
	if (frame == 19)
		frame = 0;
/*		
	while (1) {

		hRet = lpDest->BltFast(xPos + iClipTop, yPos, lpDDNormal, &rcRect, DDBLTFAST_SRCCOLORKEY);
			
		if (hRet == DD_OK)
			break;
		
		if (hRet == DDERR_SURFACELOST)
			return FALSE;
		
		if (hRet != DDERR_WASSTILLDRAWING)
			break;
	}
	*/
		return TRUE;
}
