#include "PlayerBullet1.h"

PlayerBullet1::PlayerBullet1() {

	xPos = 0;
	yPos = 0;

	width = 48;
	height = 52;

	frame = 0;
	iType = 0;

	speed = 14;
	power = 20;

	isDestroy = 0;
	
	// Create the surface from bitmap
	HRESULT				ddrval;
	lpDDNormal = NULL;
	lpDDNormal = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), 
								   MAKEINTRESOURCE(IDB_PP1Bullet), 
								   0, 0 );

	if ( lpDDNormal == NULL )
		throw GameError("Error in DDLoadBitmap of Bullet");

	// Set the ColorKey using the pixel in the top-left
	ddrval = Graphics()->DDSetColorKey( lpDDNormal, CLR_INVALID );
	if ( ddrval!= DD_OK )
		throw GameError("Error in DDSetColorKey" );

} // The end of Constructor

PlayerBullet1::~PlayerBullet1() {

	SafeRelease( lpDDNormal );

} // The end of Destructor
int PlayerBullet1::getType() const {

	return iType;

} // The end of Method getType

const void PlayerBullet1::setType( const int iNewType) {

	iType = iNewType;

} // The end of Method setType

int PlayerBullet1::getXPos() const {

	return xPos;

} // The end of Method getXPos

int PlayerBullet1::getYPos() const {

	return yPos;

} // The end of getYPos

int PlayerBullet1::getWidth() const {

	return width;

} // The end of getWidth

int PlayerBullet1::getHeight() const {

	return height;

} // The end of getHeight

const void PlayerBullet1::setPower( int newp ) {

	power = newp;

} // The end of Method setPower

int PlayerBullet1::getPower() const {

	return power;

} // The end of Method getPower

const void PlayerBullet1::move(int movex, int movey) {	

	xPos += speed;

} // The end of Method move

const void PlayerBullet1::setXY(int newx, int newy) {

	xPos = newx;
	yPos = newy;

} // The end of Method setXY

const void PlayerBullet1::setDestroy( const int destroy ) {

	isDestroy = destroy;

} // The end of Method setDestroy

int PlayerBullet1::getDestroy() const {

	return isDestroy;

} // The end of Method getDestroy

bool PlayerBullet1::draw( LPDIRECTDRAWSURFACE7 lpDest, int ppx, int ppy ) {

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

const void PlayerBullet1::checkDestroy() {

//	if ( ( xPos < 0 ) || ( xPos > 640 ) )
	if ( ( xPos > 640 ) )
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

const void PlayerBullet1::setMaxPower( int  maxpower) 
{

}
