#include "PlayerBaseBullet.h"

PlayerBaseBullet::PlayerBaseBullet() {

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

} // The end of Constructor

PlayerBaseBullet::~PlayerBaseBullet() {

	SafeRelease( lpDDNormal );

} // The end of Destructor
int PlayerBaseBullet::getType() const {

	return iType;

} // The end of Method getType

const void PlayerBaseBullet::setType( const int iNewType) {

	iType = iNewType;

} // The end of Method setType

int PlayerBaseBullet::getXPos() const {

	return xPos;

} // The end of Method getXPos

int PlayerBaseBullet::getYPos() const {

	return yPos;

} // The end of getYPos

int PlayerBaseBullet::getWidth() const {

	return width;

} // The end of getWidth

int PlayerBaseBullet::getHeight() const {

	return height;

} // The end of getHeight

const void PlayerBaseBullet::setPower( int newp ) {

	power = newp;

} // The end of Method setPower

int PlayerBaseBullet::getPower() const {

	return power;

} // The end of Method getPower
	
const void PlayerBaseBullet::move() {

	xPos += speed;

} // The end of Method move

const void PlayerBaseBullet::setXY(int newx, int newy) {

	xPos = newx;
	yPos = newy;

} // The end of Method setXY

const void PlayerBaseBullet::setDestroy( const int destroy ) {

	isDestroy = destroy;

} // The end of Method setDestroy

int PlayerBaseBullet::getDestroy() const {

	return isDestroy;

} // The end of Method getDestroy

bool PlayerBaseBullet::draw( LPDIRECTDRAWSURFACE7 lpDest ) {

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

			if ( hRet !=DD_OK )
				throw GameError("Error in function BltFast");
		}

		
		move();
	}
	
	
	return TRUE;

} // The end of Method draw

const void PlayerBaseBullet::checkDestroy() {

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

	


