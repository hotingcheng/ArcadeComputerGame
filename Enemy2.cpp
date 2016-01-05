#include "Enemy2.h"

//	DWORD  dwLastShoot;
Enemy2::Enemy2( int time , int level) {

	explosion = new cSound("explosion.wav");

	timeAppear = time;

	appear = false;
	point = 200;
	xPos = xPos = 640 - rand()%250;;
	yPos = 0;
	width = 70;
	height = 70;

	argYPos = 0;
	argXPos = 0;

	strength = 20*level;
	speed = rand()%6+1;

	S = new Strategy2_1;

	amDown = 0;

	// 0 - normal state
	// 1 - explosion frame
	// 2 - out of left boundary , delete
	state = 0;
	frame = 1;
	explosionFrame = 1;
	
	iType = 0;
	iStr = 1;
	
	iExtra = 0;
	next = NULL;
	iQtdeDown = 80;
	
	tempBullet = NULL;
	
	
	// Load the bitmap to the surface
	HRESULT				ddrval;

	lpDDNormal = NULL;
	lpDDNormal = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), 
								   MAKEINTRESOURCE(IDB_ENEMY2), 
								   0, 0 );

	if ( lpDDNormal == NULL )
		throw GameError("Error in DDLoadBitmap of Enemy Normal");

	// Set the ColorKey using the pixel in the top-left
	ddrval = Graphics()->DDSetColorKey( lpDDNormal, CLR_INVALID );
	if ( ddrval!= DD_OK )
		throw GameError(" Error in DDSetColorKey " );



	// Create the surface from bitmap 
	lpDDExplosion = NULL;
	lpDDExplosion = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), 
								   MAKEINTRESOURCE(IDB_EXPLOSION2), 
								   0, 0 );

	if ( lpDDExplosion == NULL )
		throw GameError("Error in DDLoadBitmap of Enemy Explosion");

	// Set the ColorKey using the pixel in the top-left
	ddrval = Graphics()->DDSetColorKey( lpDDExplosion, CLR_INVALID );
	if ( ddrval!= DD_OK )
		throw GameError(" Error in DDSetColorKey " );



} // The end of Constructor

Enemy2::~Enemy2() {

	
	delete S;
	SafeRelease(lpDDNormal);
	SafeRelease(lpDDExplosion);

} // The end of Destructor

int Enemy2::getStr() const {

	return iStr;

} // The end of Method getStr

const void Enemy2::setStr( const int iQtde ) {

	iStr = iQtde;

} // The end of Method setStr
	
const void Enemy2::lowStr( const int iQtde ) {

		iStr -= iQtde;

} // The end of Method lowStr

const void Enemy2::setQtdeDown( const int iNewQtde ) {

		iQtdeDown = iNewQtde;

} // The end of Method setQudeDown


BaseTreasure* Enemy2::createTreasure( const int iFlags) {

	int iPercent = rand() % 5;

	if (iFlags == iPercent) 
	{
		switch(iPercent)
		{
			case 0: 
				return new Treasure1;
			case 1:
				return new Treasure2;
			case 2:
				return new Treasure3;
//			case 3:
//				break;
//			case 4:
//				break;
			default:
				break;
		}
	}

	return NULL;
	/*
	int		iPercent;
	iPercent = rand() % 150;
	
	if ((iPercent == 0 || iPercent == 25 || iPercent == 45) &&
		(iFlags != 2))
	iExtra = 2;
	if (iPercent > 0 && iPercent < 11)
		iExtra = 3;
	if (iPercent > 10 && iPercent < 25)
		iExtra = 1;
	if (iPercent > 25 && iPercent < 45)
		iExtra = 4;
	if (iPercent == 45 || iPercent == 46)
		iExtra = 5;
	return iExtra;
*/
} // The end of Method createTreasure

int Enemy2::getTreasure() const {

		return iExtra;

} // The end of Method getTreasure

const void Enemy2::setAmDown( const int newAmDown) {

		amDown = newAmDown;

} // The end of Method setAmDown

int Enemy2::getAmDown() const {

		return amDown;

} // The end of Method getAmDown


const void Enemy2::setStrength( const int newStrength ) {

		strength = newStrength;
		
		if (strength <= 0)
			setState(1);

} // The end of Method setStrength

int Enemy2::getStrength() const {

	return strength;

} // The end of Method getStrength


const void Enemy2::setSpeed( const int newSpeed ) {

	speed = newSpeed;

} // The end of Method setSpeed

int Enemy2::getSpeed() const {

	return speed;

} // The end of Method getSpeed

const void Enemy2::setXY( const int newx, const int newy) {

	xPos = newx;
	yPos = newy;

} // The end of Method Enemy2

int Enemy2::getXPos() const {

		return xPos;

} // The end of Method getX

int Enemy2::getYPos() const {

		return yPos;

} // The end of Method getYPos

int Enemy2::getWidth() const {

		return width;

} // The end of Method getWidth

int Enemy2::getHeight() const {

		return height;

} // The end of Method getHeight

BaseEnemy* Enemy2::getNext() const {

		return next;

} // The end of Method getNext

const void Enemy2::setNext( BaseEnemy* nxEnemy) {

		next = nxEnemy;

} // The end of Method setNext

const void Enemy2::setState( const int iNewState) {

	state = iNewState;

} // The end of Method setState


int Enemy2::move(int iFlags) {


		return TRUE;
	}

bool Enemy2::isExploding() const {

	if ( state == 0)
		return FALSE;
	else
		return TRUE;

} // The end of Method isExploding

bool Enemy2::isDropExtra() const {

	if ( state == 1 && explosionFrame == 12 && iExtra != 0 )
		return TRUE;
	else
		return FALSE;

} // The end of Method isDropExtra

bool Enemy2::isDestroyMe() const {

	if (( state == 1 && explosionFrame >= 25) || state == 2)
		return TRUE;
	return FALSE;

} // The end of Method isDestroyMe

HRESULT Enemy2::draw( LPDIRECTDRAWSURFACE7 lpDest ) {

	RECT		srcRect;
	RECT		destRect;
	HRESULT		hRet;


	srcRect.left = argXPos;
	srcRect.top = argYPos;
	srcRect.right = argXPos + 70;
	srcRect.bottom = argYPos + 70;

	destRect.left = xPos;
	destRect.top = yPos;
	destRect.right = xPos + 70;
	destRect.bottom = yPos + 70;

	checkBoundary();
	
	
	if ( state == 0 ) 
	{
		
		if (lpDDNormal!=NULL)
		{
			hRet = lpDest->BltFast( xPos, yPos, lpDDNormal, 
								   &srcRect, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);
			updateFrame();
		}
	}
	else if (state == 1)
	{
		if(lpDDNormal!=NULL)
		{
			hRet = lpDest->BltFast( xPos, yPos, lpDDExplosion, 
								   &srcRect, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);
			updateExplosionFrame();		
		}
	}	
	else if (state == 2)
	{
//		delete S;
//		SafeRelease(lpDDNormal);
//		SafeRelease(lpDDExplosion);

	}

	
	return hRet;
	
}; // The end of Method draw

const void Enemy2::checkBoundary() {

	if ( xPos < 10 )
	{
		state = 2;
		xPos = 10;
	}
	if ( xPos > 640 )
		xPos = 640;
	
	if ( yPos > 410 )
	{		
//		yPos = 410;
		state = 2;
	}
	if ( yPos < 0 )
	{
//		yPos = 0;
		state = 2;
	}

} // The end of Method checkBoundary

const void Enemy2::updateFrame() {

		frame++;
	if ( frame > 50 )
		frame = 1;

	argXPos += 70;

	if ( argXPos >= 350 ) {

		argXPos = 0;
		argYPos += 70;

		if ( argYPos >= 700 ) {

			argYPos = 0;

		}

	}

} // The end of Method updateFrame

const void Enemy2::updateExplosionFrame() { 

	explosionFrame++;
	if ( explosionFrame > 21 )
		explosionFrame = 25;

	argXPos += 70;

	if ( argXPos >= 350 ) {

		argXPos = 0;
		argYPos += 70;

		if ( argYPos >= 280 ) {

			argYPos = 0;

		}

	}

} // The end of Method updateExplosionFrame

BaseBullet* Enemy2::Attack()
{
	tempBullet = new EnemyBullet2;
	tempBullet->setXY ( xPos-5, yPos+20 );
	return tempBullet;

}

int Enemy2::getState() const
{
	return state;
}

int Enemy2::getTimeAppear()
{
	return timeAppear;
}

Strategy *Enemy2::getStrategy()
{
	return S;
}

bool Enemy2::CheckHit(vector<BaseBullet*> playerbulletList)
{
	bool hit=false;
	int count=0;

	for (vector<BaseBullet* >::iterator i=playerbulletList.begin(); i!=playerbulletList.end(); i++) 
	{

		if (*i != NULL)
		{
			if ( (*i)->getXPos() + (*i)->getWidth() - 10 > getXPos() && // top-rigth
				(*i)->getXPos() < getXPos()+getWidth()        && // top-left
				(*i)->getYPos() + ( *i)->getHeight() - 15> getYPos()     && // bottom-left
			 	(*i)->getYPos() + 15 < getYPos()+getHeight() )        // bottom-
			{
				int temp = (*i)->getPower();
				(*i)->setPower ( (*i)->getPower() -strength);

				setStrength(strength - temp);

				if ( (*i)->getPower() <= 0)
					(*i)->setDestroy( 1 );				
				
				if ( !explosion->IsPlaying() )
					explosion->Play();

				hit = true;

			 }
		}
	
	}

	return hit;
}

int Enemy2::getpoint()
{
	return point;
}



void Enemy2::setappear()
{
	appear = true;
}

bool Enemy2::getappear()
{
	return appear; 
}
