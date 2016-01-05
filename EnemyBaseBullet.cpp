#include "EnemyBaseBullet.h"

EnemyBaseBullet::EnemyBaseBullet() {

	xPos = 600;
	yPos = 200;

	width = 22;
	height = 20;

	frame = 0;
	iType = 0;

	speed = 8;
	power = 10;

	isDestroy = 0;
	
	// Create the surface from bitmap
	HRESULT				ddrval;
	lpDDNormal = NULL;
	lpDDNormal = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), 
								   MAKEINTRESOURCE(IDB_EnemyBullet1), 
								   0, 0 );

	if ( lpDDNormal == NULL )
		throw GameError("Error in DDLoadBitmap of Bullet");

	// Set the ColorKey using the pixel in the top-left
	ddrval = Graphics()->DDSetColorKey( lpDDNormal, CLR_INVALID );
	if ( ddrval!= DD_OK )
		throw GameError("Error in DDSetColorKey" );

} // The end of Constructor

EnemyBaseBullet::~EnemyBaseBullet() {

	SafeRelease( lpDDNormal );

} // The end of Destructor
int EnemyBaseBullet::getType() const {

	return iType;

} // The end of Method getType

const void EnemyBaseBullet::setType( const int iNewType) {

	iType = iNewType;

} // The end of Method setType

int EnemyBaseBullet::getXPos() const {

	return xPos;

} // The end of Method getXPos

int EnemyBaseBullet::getYPos() const {

	return yPos;

} // The end of getYPos

int EnemyBaseBullet::getWidth() const {

	return width;

} // The end of getWidth

int EnemyBaseBullet::getHeight() const {

	return height;

} // The end of getHeight

const void EnemyBaseBullet::setPower( int newp ) {

	power = newp;

} // The end of Method setPower

int EnemyBaseBullet::getPower() const {

	return power;

} // The end of Method getPower
	
const void EnemyBaseBullet::move() {

	xPos -= speed;

} // The end of Method move

const void EnemyBaseBullet::setXY(int newx, int newy) {

	xPos = newx;
	yPos = newy;

} // The end of Method setXY

const void EnemyBaseBullet::setDestroy( const int destroy ) {

	isDestroy = destroy;

} // The end of Method setDestroy

int EnemyBaseBullet::getDestroy() const {

	return isDestroy;

} // The end of Method getDestroy

bool EnemyBaseBullet::draw( LPDIRECTDRAWSURFACE7 lpDest ) {

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

const void EnemyBaseBullet::checkDestroy() {

	if ( ( xPos < 0 ) )
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

	


