#include "EnemyBullet4.h"

EnemyBullet4::EnemyBullet4() {

	xPos = 600;
	yPos = 200;

	width = 26;
	height = 25;

	frame = 0;
	iType = 0;

	speed = 8;
	power = 20;

	isDestroy = 0;
	
	// Create the surface from bitmap
	HRESULT				ddrval;
	lpDDNormal = NULL;
	lpDDNormal = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), 
								   MAKEINTRESOURCE(IDB_EnemyBullet4), 
								   0, 0 );

	if ( lpDDNormal == NULL )
		throw GameError("Error in DDLoadBitmap of Bullet");

	// Set the ColorKey using the pixel in the top-left
	ddrval = Graphics()->DDSetColorKey( lpDDNormal, CLR_INVALID );
	if ( ddrval!= DD_OK )
		throw GameError("Error in DDSetColorKey" );

} // The end of Constructor

EnemyBullet4::~EnemyBullet4() {

	SafeRelease( lpDDNormal );

} // The end of Destructor
int EnemyBullet4::getType() const {

	return iType;

} // The end of Method getType

const void EnemyBullet4::setType( const int iNewType) {

	iType = iNewType;

} // The end of Method setType

int EnemyBullet4::getXPos() const {

	return xPos;

} // The end of Method getXPos

int EnemyBullet4::getYPos() const {

	return yPos;

} // The end of getYPos

int EnemyBullet4::getWidth() const {

	return width;

} // The end of getWidth

int EnemyBullet4::getHeight() const {

	return height;

} // The end of getHeight

const void EnemyBullet4::setPower( int newp ) {

	power = newp;

} // The end of Method setPower

int EnemyBullet4::getPower() const {

	return power;

} // The end of Method getPower
	
const void EnemyBullet4::move(int movex, int movey) {

	xPos -= speed;

} // The end of Method move

const void EnemyBullet4::setXY(int newx, int newy) {

	xPos = newx;
	yPos = newy;

} // The end of Method setXY

const void EnemyBullet4::setDestroy( const int destroy ) {

	isDestroy = destroy;

} // The end of Method setDestroy

int EnemyBullet4::getDestroy() const {

	return isDestroy;

} // The end of Method getDestroy

bool EnemyBullet4::draw( LPDIRECTDRAWSURFACE7 lpDest, int ppx, int ppy ) {

	HRESULT		hRet;
	DDSURFACEDESC2	ddsd;

	checkDestroy();

	ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    lpDDNormal->GetSurfaceDesc(&ddsd);

	if ( !isDestroy ) {

//		while (1)
		if ((ddsd.dwWidth + xPos < 640 ) && (ddsd.dwHeight + yPos < 480 ))
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

const void EnemyBullet4::checkDestroy() {

	if ( ( xPos < 0 ) )
	{
		isDestroy = true;
		yPos = -20;
	}


	if ( ( yPos < 0 ) || ( yPos > 460 ) )
	{
		isDestroy = true;
//		yPos = -10;
	}

} // The end of Method checkDestroy

void EnemyBullet4::trackplayerposition()
{
}

	


