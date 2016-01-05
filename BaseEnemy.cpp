#include "BaseEnemy.h"

//	DWORD  dwLastShoot;
BaseEnemy::BaseEnemy( int time ) {

} // The end of Constructor

BaseEnemy::~BaseEnemy() {

	
	SafeDelete( S);
	SafeRelease(lpDDNormal);
	SafeRelease(lpDDExplosion);

} // The end of Destructor

int BaseEnemy::getStr() const {

	return iStr;

} // The end of Method getStr

const void BaseEnemy::setStr( const int iQtde ) {

	iStr = iQtde;

} // The end of Method setStr
	
const void BaseEnemy::lowStr( const int iQtde ) {

		iStr -= iQtde;

} // The end of Method lowStr

const void BaseEnemy::setQtdeDown( const int iNewQtde ) {

		iQtdeDown = iNewQtde;

} // The end of Method setQudeDown


int BaseEnemy::createTreasure( const int iFlags) {

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

} // The end of Method createTreasure

int BaseEnemy::getTreasure() const {

		return iExtra;

} // The end of Method getTreasure

const void BaseEnemy::setAmDown( const int newAmDown) {

		amDown = newAmDown;

} // The end of Method setAmDown

int BaseEnemy::getAmDown() const {

		return amDown;

} // The end of Method getAmDown


const void BaseEnemy::setStrength( const int newStrength ) {

		strength = newStrength;

} // The end of Method setStrength

int BaseEnemy::getStrength() const {

	return strength;

} // The end of Method getStrength


const void BaseEnemy::setSpeed( const int newSpeed ) {

	speed = newSpeed;

} // The end of Method setSpeed

int BaseEnemy::getSpeed() const {

	return speed;

} // The end of Method getSpeed

const void BaseEnemy::setXY( const int newx, const int newy) {

	xPos = newx;
	yPos = newy;

} // The end of Method BaseEnemy

int BaseEnemy::getXPos() const {

		return xPos;

} // The end of Method getX

int BaseEnemy::getYPos() const {

		return yPos;

} // The end of Method getYPos

int BaseEnemy::getWidth() const {

		return width;

} // The end of Method getWidth

int BaseEnemy::getHeight() const {

		return height;

} // The end of Method getHeight

BaseEnemy* BaseEnemy::getNext() const {

		return next;

} // The end of Method getNext

const void BaseEnemy::setNext( BaseEnemy* nxEnemy) {

		next = nxEnemy;

} // The end of Method setNext

const void BaseEnemy::setState( const int iNewState) {

	state = iNewState;

} // The end of Method setState


int BaseEnemy::move(int iFlags) {


		return TRUE;
	}

bool BaseEnemy::isExploding() const {

	if ( state == 0)
		return FALSE;
	else
		return TRUE;

} // The end of Method isExploding

bool BaseEnemy::isDropExtra() const {

	if ( state == 1 && explosionFrame == 12 && iExtra != 0 )
		return TRUE;
	else
		return FALSE;

} // The end of Method isDropExtra

bool BaseEnemy::isDestroyMe() const {

	if (( state == 1 && explosionFrame >= 25) || state == 2)
		return TRUE;
	return FALSE;

} // The end of Method isDestroyMe

HRESULT BaseEnemy::draw( LPDIRECTDRAWSURFACE7 lpDest ) {

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

const void BaseEnemy::checkBoundary() {

	if ( xPos < 10 )
	{
		state = 2;
		xPos = 10;
	}
	if ( xPos > 640 )
		xPos = 640;
	if ( yPos > 410 )
		yPos = 410;
	if ( yPos < 0 )
		yPos = 0;

} // The end of Method checkBoundary

const void BaseEnemy::updateFrame() {

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

const void BaseEnemy::updateExplosionFrame() { 

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

BaseBullet* BaseEnemy::Attack()
{
	tempBullet = new EnemyBaseBullet;
	tempBullet->setXY ( xPos-5, yPos+20 );
	return tempBullet;

}

int BaseEnemy::getState() const
{
	return state;
}

int BaseEnemy::getTimeAppear()
{
	return timeAppear;
}

Strategy *BaseEnemy::getStrategy()
{
	return S;
}

bool BaseEnemy::CheckHit(vector<BaseBullet*> playerbulletList)
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
				setState( 1 );

				(*i)->setPower ( (*i)->getPower() -10);
				
				if ( (*i)->getPower() == 0)
					(*i)->setDestroy( 1 );				
				
				if ( !explosion->IsPlaying() )
					explosion->Play();

				hit = true;

			 }
		}
	
	}

	return hit;
}

int BaseEnemy::getpoint()
{
	return point;
}


