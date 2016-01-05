#include "BigBoss1.h"

//	DWORD  dwLastShoot;
BigBoss1::BigBoss1( int time ,int level) {

	explosion = new cSound("explosion.wav");

	transform = 0;

	timeAppear = time;
	appear = false;

	point = 1000;
	xPos = 640;
	yPos = rand()%480;
	width = 146;
	height = 143;

	argYPos = 0;
	argXPos = 0;

	strength = 1000*level;
	speed = rand()%6+1;

//	S = new Strategy1(-1*speed,0);
	S = new Strategy3;

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

	if (level == 1)
	{
	
		lpDDNormal = NULL;
		lpDDNormal = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), 
									   MAKEINTRESOURCE(IDB_BigBoss1_), 
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
									   MAKEINTRESOURCE(IDB_PPexplode), 
									   0, 0 );

		if ( lpDDExplosion == NULL )
			throw GameError("Error in DDLoadBitmap of Enemy Explosion");

		// Set the ColorKey using the pixel in the top-left
		ddrval = Graphics()->DDSetColorKey( lpDDExplosion, CLR_INVALID );
		if ( ddrval!= DD_OK )
			throw GameError(" Error in DDSetColorKey " );
	}
	else 
	{
		width = 151;
		height = 200;

		lpDDNormal = NULL;
		lpDDNormal = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), 
									   MAKEINTRESOURCE(IDB_BigBoss1Transform), 
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
									   MAKEINTRESOURCE(IDB_PPexplode), 
									   0, 0 );

		if ( lpDDExplosion == NULL )
			throw GameError("Error in DDLoadBitmap of Enemy Explosion");

		// Set the ColorKey using the pixel in the top-left
		ddrval = Graphics()->DDSetColorKey( lpDDExplosion, CLR_INVALID );
		if ( ddrval!= DD_OK )
			throw GameError(" Error in DDSetColorKey " );
	}



} // The end of Constructor

BigBoss1::~BigBoss1() {

	
	SafeDelete( S);
	SafeRelease(lpDDNormal);
	SafeRelease(lpDDExplosion);

} // The end of Destructor

int BigBoss1::getStr() const {

	return iStr;

} // The end of Method getStr

const void BigBoss1::setStr( const int iQtde ) {

	iStr = iQtde;

} // The end of Method setStr
	
const void BigBoss1::lowStr( const int iQtde ) {

		iStr -= iQtde;

} // The end of Method lowStr

const void BigBoss1::setQtdeDown( const int iNewQtde ) {

		iQtdeDown = iNewQtde;

} // The end of Method setQudeDown

BaseTreasure* BigBoss1::createTreasure( const int iFlags)	
{	
/*	int iPercent = rand() % 100;

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
		}
	}
*/
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

int BigBoss1::getTreasure() const {

		return iExtra;

} // The end of Method getTreasure

const void BigBoss1::setAmDown( const int newAmDown) {

		amDown = newAmDown;

} // The end of Method setAmDown

int BigBoss1::getAmDown() const {

		return amDown;

} // The end of Method getAmDown


const void BigBoss1::setStrength( const int newStrength ) {

		strength = newStrength;

		if (strength <= 0)
			state = 1;

} // The end of Method setStrength

int BigBoss1::getStrength() const {

	return strength;

} // The end of Method getStrength


const void BigBoss1::setSpeed( const int newSpeed ) {

	speed = newSpeed;

} // The end of Method setSpeed

int BigBoss1::getSpeed() const {

	return speed;

} // The end of Method getSpeed

const void BigBoss1::setXY( const int newx, const int newy) {

	xPos = newx;
	yPos = newy;

} // The end of Method BigBoss1

int BigBoss1::getXPos() const {

		return xPos;

} // The end of Method getX

int BigBoss1::getYPos() const {

		return yPos;

} // The end of Method getYPos

int BigBoss1::getWidth() const {

		return width;

} // The end of Method getWidth

int BigBoss1::getHeight() const {

		return height;

} // The end of Method getHeight

BaseEnemy* BigBoss1::getNext() const {

		return next;

} // The end of Method getNext

const void BigBoss1::setNext( BaseEnemy* nxEnemy) {

		next = nxEnemy;

} // The end of Method setNext

const void BigBoss1::setState( const int iNewState) {

	state = iNewState;

} // The end of Method setState


int BigBoss1::move(int iFlags) {


		return TRUE;
	}

bool BigBoss1::isExploding() const {

	if ( state == 0)
		return FALSE;
	else
		return TRUE;

} // The end of Method isExploding

bool BigBoss1::isDropExtra() const {

	if ( state == 1 && explosionFrame == 12 && iExtra != 0 )
		return TRUE;
	else
		return FALSE;

} // The end of Method isDropExtra

bool BigBoss1::isDestroyMe() const {

	if (( state == 1 && explosionFrame >= 7) || state == 2)
		return TRUE;
	return FALSE;

} // The end of Method isDestroyMe

HRESULT BigBoss1::draw( LPDIRECTDRAWSURFACE7 lpDest ) {

	RECT		srcRect;
	RECT		destRect;
	HRESULT		hRet;


	srcRect.left = argXPos;
	srcRect.top = argYPos;
	srcRect.right = argXPos + width;
	srcRect.bottom = argYPos + height;

	destRect.left = xPos;
	destRect.top = yPos;
	destRect.right = xPos + width;
	destRect.bottom = yPos + height;

	checkBoundary();
	
	
	if ( state == 0 ) 
	{
		
		if (lpDDNormal!=NULL)
		{
			hRet = lpDest->BltFast( xPos, yPos, lpDDNormal, 
								   &srcRect, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);
	//		updateFrame();
		}
	}
	else if (state == 1)
	{
		srcRect.left = argXPos;
		srcRect.top = argYPos;
		srcRect.right = argXPos + 70;
		srcRect.bottom = argYPos + 70;

		destRect.left = xPos;
		destRect.top = yPos;
		destRect.right = xPos + 70;
		destRect.bottom = yPos + 70;


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

const void BigBoss1::checkBoundary() {

	if ( xPos < 10 )
	{
		xPos = 10;
		
	}

	if ( xPos > 610 )
		xPos = 610;

	if ( yPos > 270 )
	{		
		yPos = 270;
		
	}
	if ( yPos < 0 )
	{
		yPos = 0;
		
	}

} // The end of Method checkBoundary

const void BigBoss1::updateFrame() {

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

const void BigBoss1::updateExplosionFrame() { 

	explosionFrame++;
	if ( explosionFrame > 7 )
		explosionFrame = 7;

	argXPos += 70;

	if ( argXPos >= 350 ) {

		argXPos = 0;
		argYPos += 70;

		if ( argYPos >= 280 ) {

			argYPos = 0;

		}

	}

} // The end of Method updateExplosionFrame

BaseBullet* BigBoss1::Attack()
{	
	if (strength > 1200)
	{	
		int t = rand() % 10;

		if (t == 0)
			tempBullet = new EnemyBullet2;
		else if (t == 1)
			tempBullet = new EnemyBullet3;
		else if (t == 2)
			tempBullet = new EnemyBullet4;
		else if (t == 3)
			tempBullet = new EnemyBullet4;
		else
			tempBullet = new EnemyBullet7;

		tempBullet->setXY ( xPos, yPos+30 );

		return tempBullet;
	}
//	else if (strength > 150 && strength <= 300) 
	else if (strength > 750 && strength <= 1200) 
	{		
		if (transform==0)
		{
			SafeDelete( S);
			S = new Strategy4;
			transform++;
		}

		if (rand() % 2==0)
			tempBullet = new EnemyBullet8;
		else
			tempBullet = new EnemyBullet7;

		tempBullet->setXY ( xPos, yPos+30 );
		return tempBullet;
	}
	else
	{
		if (transform == 1)
		{
			SafeDelete( S);
			S = new Strategy3;

			SafeRelease(lpDDNormal);

			lpDDNormal = NULL;
			
			while ( lpDDNormal == NULL)			
				lpDDNormal = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), 
										   MAKEINTRESOURCE(IDB_BigBoss1Transform), 
										   0, 0 );

			width = 151;
			height = 200;

			HRESULT ddrval;
			while  (ddrval != DD_OK)
				ddrval = Graphics()->DDSetColorKey( lpDDNormal, CLR_INVALID );

//			if ( ddrval!= DD_OK )
//				throw GameError(" Error in DDSetColorKey " );
		
			transform++;
		}

		if (rand() % 3 == 0)
		{
			tempBullet = new BigBossAttack;
			tempBullet->setXY ( xPos, yPos );
			return tempBullet;
		}
		else
			return NULL;
	}
}

int BigBoss1::getState() const
{
	return state;
}

int BigBoss1::getTimeAppear()
{
	return timeAppear;
}

Strategy *BigBoss1::getStrategy()
{
	return S;
}

bool BigBoss1::CheckHit(vector<BaseBullet*> playerbulletList)
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

int BigBoss1::getpoint()
{
	return point;
}

void BigBoss1::setappear()
{
	appear = true;
}

bool BigBoss1::getappear()
{
	return appear; 
}
