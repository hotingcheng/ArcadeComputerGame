#include "Leader1.h"

//	DWORD  dwLastShoot;
Leader1::Leader1( int time, int level ) {

	explosion = new cSound("explosion.wav");

	appear = false;
	timeAppear = time;

	point = 300;
	xPos = 640;
	yPos = rand()%480;
	width = 207;
	height = 71;

	argYPos = 0;
	argXPos = 0;

	strength = 200*level;
	speed = 2;

	S = new Strategy4;

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
								   MAKEINTRESOURCE(IDB_Leader1_), 
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



} // The end of Constructor

Leader1::~Leader1() {

	
	delete S;
	SafeRelease(lpDDNormal);
	SafeRelease(lpDDExplosion);

} // The end of Destructor

int Leader1::getStr() const {

	return iStr;

} // The end of Method getStr

const void Leader1::setStr( const int iQtde ) {

	iStr = iQtde;

} // The end of Method setStr
	
const void Leader1::lowStr( const int iQtde ) {

		iStr -= iQtde;

} // The end of Method lowStr

const void Leader1::setQtdeDown( const int iNewQtde ) {

		iQtdeDown = iNewQtde;

} // The end of Method setQudeDown

BaseTreasure* Leader1::createTreasure( const int iFlags)	
{	
	int iPercent = rand() % 100;

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
			case 3:
				return new Treasure4;
			case 4:
				return new Treasure5;
			default:
				break;

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

int Leader1::getTreasure() const {

		return iExtra;

} // The end of Method getTreasure

const void Leader1::setAmDown( const int newAmDown) {

		amDown = newAmDown;

} // The end of Method setAmDown

int Leader1::getAmDown() const {

		return amDown;

} // The end of Method getAmDown


const void Leader1::setStrength( const int newStrength ) {

		strength = newStrength;

		if (strength <= 0)
			state = 1;

} // The end of Method setStrength

int Leader1::getStrength() const {

	return strength;

} // The end of Method getStrength


const void Leader1::setSpeed( const int newSpeed ) {

	speed = newSpeed;

} // The end of Method setSpeed

int Leader1::getSpeed() const {

	return speed;

} // The end of Method getSpeed

const void Leader1::setXY( const int newx, const int newy) {

	xPos = newx;
	yPos = newy;

} // The end of Method Leader1

int Leader1::getXPos() const {

		return xPos;

} // The end of Method getX

int Leader1::getYPos() const {

		return yPos;

} // The end of Method getYPos

int Leader1::getWidth() const {

		return width;

} // The end of Method getWidth

int Leader1::getHeight() const {

		return height;

} // The end of Method getHeight

BaseEnemy* Leader1::getNext() const {

		return next;

} // The end of Method getNext

const void Leader1::setNext( BaseEnemy* nxEnemy) {

		next = nxEnemy;

} // The end of Method setNext

const void Leader1::setState( const int iNewState) {

	state = iNewState;

} // The end of Method setState


int Leader1::move(int iFlags) {


		return TRUE;
	}

bool Leader1::isExploding() const {

	if ( state == 0)
		return FALSE;
	else
		return TRUE;

} // The end of Method isExploding

bool Leader1::isDropExtra() const {

	if ( state == 1 && explosionFrame == 12 && iExtra != 0 )
		return TRUE;
	else
		return FALSE;

} // The end of Method isDropExtra

bool Leader1::isDestroyMe() const {

	if (( state == 1 && explosionFrame >= 7) || state == 2)
		return TRUE;
	return FALSE;

} // The end of Method isDestroyMe

HRESULT Leader1::draw( LPDIRECTDRAWSURFACE7 lpDest ) {

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

const void Leader1::checkBoundary() {

	if ( xPos < 10 )
	{
		state = 2;
		xPos = 10;
	}

	if ( xPos > 610 )
		xPos = 610;

	if ( yPos > 410 )
	{		
		yPos = 410;
//		state = 2;
	}
	if ( yPos < 0 )
	{
		yPos = 0;
//		state = 2;
	}

} // The end of Method checkBoundary

const void Leader1::updateFrame() {

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

const void Leader1::updateExplosionFrame() { 

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

BaseBullet* Leader1::Attack()
{
	tempBullet = new EnemyBullet4;
	tempBullet->setXY ( xPos-5, yPos+20 );
	return tempBullet;

}

int Leader1::getState() const
{
	return state;
}

int Leader1::getTimeAppear()
{
	return timeAppear;
}

Strategy *Leader1::getStrategy()
{
	return S;
}

bool Leader1::CheckHit(vector<BaseBullet*> playerbulletList)
{
	bool hit=false;
	int count=0;

	for (vector<BaseBullet* >::iterator i=playerbulletList.begin(); i!=playerbulletList.end(); i++) 
	{

		if (*i != NULL)
		{
			if ( (*i)->getXPos() + (*i)->getWidth()  > getXPos() && // top-rigth
				(*i)->getXPos() < getXPos()+getWidth()        && // top-left
				(*i)->getYPos() + ( *i)->getHeight() > getYPos()     && // bottom-left
			 	(*i)->getYPos()  < getYPos()+getHeight() )        // bottom-
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

int Leader1::getpoint()
{
	return point;
}



void Leader1::setappear()
{
	appear = true;
}

bool Leader1::getappear()
{
	return appear; 
}