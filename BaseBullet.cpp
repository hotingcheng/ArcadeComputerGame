#include "BaseBullet.h"

BaseBullet::BaseBullet() {
/*
	xPos = 0;
	yPos = 0;

	width = 87;
	height = 57;

	frame = 0;
	iType = 0;

	speed = 10;
	power = 10;

	isDestroy = 0;
	
	// Create the surface from bitmap
	HRESULT				ddrval;
	lpDDNormal = NULL;
	lpDDNormal = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), 
								   MAKEINTRESOURCE(IDB_PP2Bullet), 
								   0, 0 );

	if ( lpDDNormal == NULL )
		throw GameError("Error in DDLoadBitmap of Bullet");

	// Set the ColorKey using the pixel in the top-left
	ddrval = Graphics()->DDSetColorKey( lpDDNormal, CLR_INVALID );
	if ( ddrval!= DD_OK )
		throw GameError("Error in DDSetColorKey" );
*/
} // The end of Constructor

BaseBullet::~BaseBullet() {

	SafeRelease( lpDDNormal );

} // The end of Destructor
int BaseBullet::getType() const {

	return iType;

} // The end of Method getType

const void BaseBullet::setType( const int iNewType) {

	iType = iNewType;

} // The end of Method setType

int BaseBullet::getXPos() const {

	return xPos;

} // The end of Method getXPos

int BaseBullet::getYPos() const {

	return yPos;

} // The end of getYPos

int BaseBullet::getWidth() const {

	return width;

} // The end of getWidth

int BaseBullet::getHeight() const {

	return height;

} // The end of getHeight

const void BaseBullet::setPower( int newp ) {

	power = newp;

} // The end of Method setPower

int BaseBullet::getPower() const {

	return power;

} // The end of Method getPower
	
const void BaseBullet::move(int movex, int movey) {

	xPos += speed;

} // The end of Method move

const void BaseBullet::setXY(int newx, int newy) {

	xPos = newx;
	yPos = newy;

} // The end of Method setXY

const void BaseBullet::setDestroy( const int destroy ) {

	isDestroy = destroy;

} // The end of Method setDestroy

int BaseBullet::getDestroy() const {

	return isDestroy;

} // The end of Method getDestroy

bool BaseBullet::draw( LPDIRECTDRAWSURFACE7 lpDest, int ppx, int ppy ) {

	HRESULT		hRet;
	DDSURFACEDESC2	ddsd;

	checkDestroy();

	ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    lpDDNormal->GetSurfaceDesc(&ddsd);

	if ( !isDestroy ) {

//		while (1)
		if (ddsd.dwWidth + xPos < 640 ) 
		{
			hRet = lpDest->BltFast(xPos, yPos, lpDDNormal, NULL, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);

//			if (hRet == DD_OK)
//				break;

//			if ( hRet !=DD_OK )
//				throw GameError("Error in function BltFast");
		}
		
		move(0,0);
	}
	
	
	return TRUE;

} // The end of Method draw

const void BaseBullet::checkDestroy() {

	if ( ( xPos < 0 ) || ( xPos > 640 ) )
	{
		isDestroy = true;
//		yPos = -10;
	}


	if ( ( yPos < 0 ) || ( yPos > 460 ) )
	{
		isDestroy = true;
//		yPos = -10;
	}

} // The end of Method checkDestroy

	


