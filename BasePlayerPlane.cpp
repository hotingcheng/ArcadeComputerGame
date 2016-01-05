#include "BasePlayerPlane.h"

BasePlayerPlane::BasePlayerPlane() {

	/*
    PlayerScore = new Score;

	xPos = 70;
	yPos = 200;
	argYPos = 0;
	argXPos = 0;
	
	speed = 7;
	strength = 1;

	state = 0;
	frame = 1;
	explosionFrame = 1;

	tempBullet = NULL;

	isShoot = false;

	bulletList.clear();

	sound = new cSound( "playershoot.wav");

	Input()->getKeyboard()->setReceiver( this );

	// Create a surface of normal from the bitmap and set the colorkey
	HRESULT ddrval;

	lpDDNormal = NULL;
	lpDDNormal =  Graphics()->DDLoadBitmap( Graphics()->getDirectDraw(), 
								MAKEINTRESOURCE(IDB_PP2), 
								0, 0 );
	if ( lpDDNormal == NULL )
		throw GameError( "Error in load bitmap inPlayer Normal");

	
	ddrval = Graphics()->DDSetColorKey( lpDDNormal, CLR_INVALID );
	if ( ddrval!= DD_OK )
		throw GameError(" Error in DDSetColorKey " );
		


	// Create a surface of explosion from bitmap and set the colorkey
	lpDDExplosion = NULL;
	lpDDExplosion =  Graphics()->DDLoadBitmap( Graphics()->getDirectDraw(), 
								MAKEINTRESOURCE(IDB_PP1), 
								0, 0 );
	if ( lpDDExplosion == NULL )
		throw GameError( "Error in load bitmap inPlayer Explosion");

	
	ddrval = Graphics()->DDSetColorKey( lpDDExplosion, CLR_INVALID );
	if ( ddrval!= DD_OK )
		throw GameError(" Error in DDSetColorKey of Explosion" );

*/
} // The end of Constructor

BasePlayerPlane::~BasePlayerPlane() {

	SafeDelete(PlayerScore );		
	SafeRelease(lpDDNormal);
	SafeRelease(lpDDExplosion);

} // The end of Destructor

const void BasePlayerPlane::setStrength( const int newStrength ) {

	strength = newStrength;

} // The end of Method setStrength

int BasePlayerPlane::getStrength() const {

	return strength;

} // The end of Method getStrength


const void BasePlayerPlane::setSpeed( const int newSpeed ) {

	speed = newSpeed;

} // The end of Method setSpeed

int BasePlayerPlane::getSpeed() const {

	return speed;

} // The end of Method getSpeed

const void BasePlayerPlane::setXY( const int newx, const int newy) {

	xPos = newx;
	yPos = newy;


} // The end of Method BasePlayerPlane

int BasePlayerPlane::getXPos() const {

	return xPos;

} // The end of Method getX

int BasePlayerPlane::getYPos() const {

	return yPos;

} // The end of Method getYPos

bool BasePlayerPlane::isExploding() const {


	if ( state == 0 )
		return FALSE;
	else
		return TRUE;

} // The end of Method isExploding

bool BasePlayerPlane::isDestroyMe() const {

	if ( state == 1 && explosionFrame == 20 )
		return TRUE;
	return FALSE;

} // The end of Method isDestroyMe

HRESULT BasePlayerPlane::draw(LPDIRECTDRAWSURFACE7 lpDest ) {

	RECT		srcRect;
	RECT		destRect;
	HRESULT		hRet;

	// Draw the shield status
	DDBLTFX     ddbltfx;
	
    ddbltfx.dwSize = sizeof( ddbltfx );
	ddbltfx.dwFillColor = RGB(30,5,15);
	destRect.top = 30;
	destRect.left = 20;
	destRect.bottom = 45;
	destRect.right  = 220;

	hRet = Graphics()->getBackBuffer()->Blt(&destRect, NULL, NULL, DDBLT_COLORFILL, &ddbltfx);
	
	if ( !bulletList.empty() ) {

		for (literator i=bulletList.begin(); i!=bulletList.end(); i++) {

			if ( *i != NULL) 
			{
				if ( (*i)->getDestroy() )
				{
					delete *i;
					*i =NULL;
				}
				else
					(*i)->draw( lpDest );
			}

		}
	}

	PlayerScore->bltText("HP\0",18,10);
	PlayerScore->bltText("YOUR SCORE\0",464,8);
	PlayerScore->DrawScore(480,30);

	// draw player
	srcRect.left = argXPos;
	srcRect.top = argYPos;
	srcRect.right = argXPos + 70;
	srcRect.bottom = argYPos + 70;

	destRect.left = xPos;
	destRect.top = yPos;
	destRect.right = xPos + 70;
	destRect.bottom = yPos + 70;

	checkBoundary();

	if ( state == 0 ) {

		hRet = lpDest->BltFast(xPos, yPos, lpDDNormal, 
							   &srcRect,  DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
		updateFrame();
	}
	else {

		hRet = lpDest->BltFast(xPos, yPos, lpDDExplosion, 
							   &srcRect,  DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT );
		updateExplosionFrame();

	}
	

	return hRet;
	
}

void BasePlayerPlane::keyPresse( int key ) {

	switch( key )
	{
	case DIK_UP:
			yPos -=speed;
	
		break;
	case DIK_DOWN:
			yPos +=speed;
		
		break;
	case DIK_LEFT:
			xPos -=speed;
	
		break;
	case DIK_RIGHT:
			xPos +=speed;		
	
		break;

	case DIK_SPACE:

		if ( !isShoot ) {
			
			if ( !sound->IsPlaying() )
				sound->Play();
			isShoot = true;
			tempBullet = new BaseBullet;
			tempBullet->setXY ( xPos + 60, yPos+5); 
			bulletList.push_back( tempBullet );
			tempBullet = NULL;
		}
		
		break;


	}

} // The end of Method keyPressed

void BasePlayerPlane::keyRelease ( int key ) {
	
	isShoot = false;

} // The end of Method keyRelease

const void BasePlayerPlane::checkBoundary() {

	if ( xPos < 0 )
		xPos = 0;
	if ( xPos > 570 )
		xPos = 570;
	if ( yPos > 410 )
		yPos = 410;
	if ( yPos < 0 )
		yPos = 0;

} // The end of Method checkBoundary

const void BasePlayerPlane::updateFrame() {

	frame++;
	if ( frame > 25 )
		frame = 1;
	
	argXPos += 70;

	if ( argXPos >= 350 ) {

		argXPos = 0;
		argYPos += 70;

		if ( argYPos >= 350 ) {

			argYPos = 0;

		}

	}

} // The end of Method updateFrame

const void BasePlayerPlane::updateExplosionFrame() {

	frame++;
	if ( frame > 25 )
		frame = 1;

	argXPos += 70;

	if ( argXPos >= 490 ) {

		argXPos = 0;
		argYPos += 70;

		if ( argYPos >= 210 ) {

			argYPos = 0;

		}

	}

} // The end of Method updateExplosionFrame

vector<BaseBullet* > BasePlayerPlane::getBulletList() const {

	return bulletList;

} // The end of Method getBulletList

Score* BasePlayerPlane::getScorePt()
{
	return PlayerScore;
}
