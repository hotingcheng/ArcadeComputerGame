#include "Enemy1.h"

//	DWORD  dwLastShoot;
Enemy1::Enemy1( int time , int level) {

	explosion = new cSound("explosion.wav");

	timeAppear = time;

	appear = false;
	point = 150;
	xPos = 640;
	yPos = rand()%480;
	width = 70;
	height = 70;

	argYPos = 0;
	argXPos = 0;

	strength = 10*level;
	speed = rand()%6+1;

	S = new Strategy1(-1*speed,0);

	Trea = NULL;

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
								   MAKEINTRESOURCE(IDB_ENEMY1), 
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
								   MAKEINTRESOURCE(IDB_EXPLOSION1), 
								   0, 0 );

	if ( lpDDExplosion == NULL )
		throw GameError("Error in DDLoadBitmap of Enemy Explosion");

	// Set the ColorKey using the pixel in the top-left
	ddrval = Graphics()->DDSetColorKey( lpDDExplosion, CLR_INVALID );
	if ( ddrval!= DD_OK )
		throw GameError(" Error in DDSetColorKey " );



} // The end of Constructor

Enemy1::~Enemy1() {

	
	delete S;
	SafeRelease(lpDDNormal);
	SafeRelease(lpDDExplosion);

} // The end of Destructor

int Enemy1::getStr() const {

	return iStr;

} // The end of Method getStr

const void Enemy1::setStr( const int iQtde ) {

	iStr = iQtde;

} // The end of Method setStr
	
const void Enemy1::lowStr( const int iQtde ) {

		iStr -= iQtde;

} // The end of Method lowStr

const void Enemy1::setQtdeDown( const int iNewQtde ) {

		iQtdeDown = iNewQtde;

} // The end of Method setQudeDown

BaseTreasure* Enemy1::createTreasure( const int iFlags)	
{	
	int iPercent = rand() % 5;
//	int iPercent = 1;

	if (iFlags == iPercent) 
	{
		switch(iPercent)
		{
			case 0: 
				return new Treasure1;
			case 1:
				return new Treasure2;
//			case 2:
//				break;
//			case 3:
//				break;
//			case 4:
//				break;
//			default:
//				return NULL;
		}
	}

	return NULL;
	
/*	if ((iPercent == 0 || iPercent == 25 || iPercent == 45) &&
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

int Enemy1::getTreasure() const {

		return iExtra;

} // The end of Method getTreasure

const void Enemy1::setAmDown( const int newAmDown) {

		amDown = newAmDown;

} // The end of Method setAmDown

int Enemy1::getAmDown() const {

		return amDown;

} // The end of Method getAmDown


const void Enemy1::setStrength( const int newStrength ) {

		strength = newStrength;

		if (strength <= 0)
			state = 1;

} // The end of Method setStrength

int Enemy1::getStrength() const {

	return strength;

} // The end of Method getStrength


const void Enemy1::setSpeed( const int newSpeed ) {

	speed = newSpeed;

} // The end of Method setSpeed

int Enemy1::getSpeed() const {

	return speed;

} // The end of Method getSpeed

const void Enemy1::setXY( const int newx, const int newy) {

	xPos = newx;
	yPos = newy;

} // The end of Method Enemy1

int Enemy1::getXPos() const {

		return xPos;

} // The end of Method getX

int Enemy1::getYPos() const {

		return yPos;

} // The end of Method getYPos

int Enemy1::getWidth() const {

		return width;

} // The end of Method getWidth

int Enemy1::getHeight() const {

		return height;

} // The end of Method getHeight

BaseEnemy* Enemy1::getNext() const {

		return next;

} // The end of Method getNext

const void Enemy1::setNext( BaseEnemy* nxEnemy) {

		next = nxEnemy;

} // The end of Method setNext

const void Enemy1::setState( const int iNewState) {

	state = iNewState;

} // The end of Method setState



int Enemy1::move(int iFlags) {


		return TRUE;
	}

bool Enemy1::isExploding() const {

	if ( state == 0)
		return FALSE;
	else
		return TRUE;

} // The end of Method isExploding

bool Enemy1::isDropExtra() const {

	if ( state == 1 && explosionFrame == 12 && iExtra != 0 )
		return TRUE;
	else
		return FALSE;

} // The end of Method isDropExtra

bool Enemy1::isDestroyMe() const {

	if (( state == 1 && explosionFrame >= 25) || state == 2)
		return TRUE;
	return FALSE;

} // The end of Method isDestroyMe

HRESULT Enemy1::draw( LPDIRECTDRAWSURFACE7 lpDest ) {

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

	if (Trea != NULL)
	{
		Trea->move(2);
		Trea->draw(lpDest);
	}
	
	return hRet;
	
}; // The end of Method draw

const void Enemy1::checkBoundary() {

	if ( xPos < 10 )
	{
		state = 2;
		xPos = 10;
	}

	if ( xPos > 610 )
		xPos = 610;

	if ( yPos > 405 )
	{		
		yPos = 405;
//		state = 2;
	}
	if ( yPos < 0 )
	{
		yPos = 0;
//		state = 2;
	}

} // The end of Method checkBoundary

const void Enemy1::updateFrame() {

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

const void Enemy1::updateExplosionFrame() { 

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

BaseBullet* Enemy1::Attack()
{
	tempBullet = new EnemyBullet1;
	tempBullet->setXY ( xPos-5, yPos+20 );
	return tempBullet;

}

int Enemy1::getState() const
{
	return state;
}

int Enemy1::getTimeAppear()
{
	return timeAppear;
}

Strategy *Enemy1::getStrategy()
{
	return S;
}

bool Enemy1::CheckHit(vector<BaseBullet*> playerbulletList)
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
				{
					(*i)->setDestroy( 1 );				
				}

				if ( !explosion->IsPlaying() )
					explosion->Play();

				hit = true;

			 }
		}
	
	}

	return hit;
}

int Enemy1::getpoint()
{
	return point;
}



void Enemy1::setappear()
{
	appear = true;
}

bool Enemy1::getappear()
{
	return appear; 
}
