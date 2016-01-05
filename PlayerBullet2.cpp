#include "PlayerBullet2.h"

PlayerBullet2::PlayerBullet2() {

	xPos = 0;
	yPos = 0;

	width = 87;
	height = 57;

	frame = 0;
	iType = 0;

	speed = 10;
	power = 100;

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

} // The end of Constructor

PlayerBullet2::~PlayerBullet2() {

	SafeRelease( lpDDNormal );

} // The end of Destructor
int PlayerBullet2::getType() const {

	return iType;

} // The end of Method getType

const void PlayerBullet2::setType( const int iNewType) {

	iType = iNewType;

} // The end of Method setType

int PlayerBullet2::getXPos() const {

	return xPos;

} // The end of Method getXPos

int PlayerBullet2::getYPos() const {

	return yPos;

} // The end of getYPos

int PlayerBullet2::getWidth() const {

	return width;

} // The end of getWidth

int PlayerBullet2::getHeight() const {

	return height;

} // The end of getHeight

const void PlayerBullet2::setPower( int newp ) {

	power = newp;

} // The end of Method setPower

int PlayerBullet2::getPower() const {

	return power;

} // The end of Method getPower

const void PlayerBullet2::setMaxPower(int maxpower)
{
	HRESULT ddrval;

	if (power != maxpower*100)
	{
		power = maxpower*100;

		SafeRelease(lpDDNormal);		

		if (maxpower == 1)
		{
			width = 87;
			height = 57;

			lpDDNormal = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), MAKEINTRESOURCE(IDB_PP2Bullet), 0, 0 );
			ddrval = Graphics()->DDSetColorKey( lpDDNormal, CLR_INVALID );
		}
		else if (maxpower == 2)
		{
			width = 109;
			height = 76;

			lpDDNormal = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), MAKEINTRESOURCE(IDB_PP2Bullet_2), 0, 0 );
			ddrval = Graphics()->DDSetColorKey( lpDDNormal, CLR_INVALID );
		}
		else 
		{
			width = 151;
			height = 89;

			lpDDNormal = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), MAKEINTRESOURCE(IDB_PP2Bullet_3), 0, 0 );
			ddrval = Graphics()->DDSetColorKey( lpDDNormal, CLR_INVALID );
		}
	}
}

	
const void PlayerBullet2::move(int movex, int movey) {

	xPos += speed;

} // The end of Method move

const void PlayerBullet2::setXY(int newx, int newy) {

	xPos = newx;
	yPos = newy;

} // The end of Method setXY

const void PlayerBullet2::setDestroy( const int destroy ) {

	isDestroy = destroy;

} // The end of Method setDestroy

int PlayerBullet2::getDestroy() const {

	return isDestroy;

} // The end of Method getDestroy

bool PlayerBullet2::draw( LPDIRECTDRAWSURFACE7 lpDest , int ppx, int ppy) {

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

const void PlayerBullet2::checkDestroy() {

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

	


