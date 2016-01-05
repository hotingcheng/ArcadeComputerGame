#include "PlayerPlaneMode2.h"

PlayerPlaneMode2::PlayerPlaneMode2()
{
    PlayerScore = new Score;
	explosion = new cSound("explosion.wav");
	getT = new cSound("gettreasure.wav");
	
	NextMode = NULL;

	power = 1;

	presscnt = 40;
	changecnt = 1;
	change = false;
	xPos = 70;
	yPos = 200;
	argYPos = 0;
	argXPos = 0;
	
	speed = 4;
	HP = 600;

	width = 70;
	height = 70;

	state = -1;
	frame = 1;
	explosionFrame = 1;

	tempBullet = NULL;

//	isChange = false;
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
								MAKEINTRESOURCE(IDB_PPexplode), 
								0, 0 );
	if ( lpDDExplosion == NULL )
		throw GameError( "Error in load bitmap inPlayer Explosion");

	
	ddrval = Graphics()->DDSetColorKey( lpDDExplosion, CLR_INVALID );
	if ( ddrval!= DD_OK )
		throw GameError(" Error in DDSetColorKey of Explosion" );
}


PlayerPlaneMode2::~PlayerPlaneMode2() {

	SafeDelete(PlayerScore);
	SafeDelete(explosion);
	SafeDelete(sound);
	SafeDelete(getT);

	SafeRelease(lpDDNormal);
	SafeRelease(lpDDExplosion);

	for ( literator i = bulletList.begin(); i!=bulletList.end(); i++ ) 	
		SafeDelete( *i );

	while (!bulletList.empty())
		bulletList.pop_back();

} // The end of Destructor

const void PlayerPlaneMode2::setStrength( const int newStrength ) {

	HP = newStrength;

} // The end of Method setStrength

int PlayerPlaneMode2::getStrength() const {

	return HP;

} // The end of Method getStrength


const void PlayerPlaneMode2::setSpeed( const int newSpeed ) {

	speed = newSpeed;

} // The end of Method setSpeed

int PlayerPlaneMode2::getSpeed() const {

	return speed;

} // The end of Method getSpeed

const void PlayerPlaneMode2::setXY( const int newx, const int newy) {

	xPos = newx;
	yPos = newy;


} // The end of Method PlayerPlaneMode2

int PlayerPlaneMode2::getXPos() const {

	return xPos;

} // The end of Method getX

int PlayerPlaneMode2::getYPos() const {

	return yPos;

} // The end of Method getYPos

bool PlayerPlaneMode2::isExploding() const {


	if ( state == 0 )
		return FALSE;
	else
		return TRUE;

} // The end of Method isExploding

bool PlayerPlaneMode2::isDestroyMe() const {

	if ( state == 1 && explosionFrame == 7 )
		return TRUE;
	return FALSE;

} // The end of Method isDestroyMe

HRESULT PlayerPlaneMode2::draw(LPDIRECTDRAWSURFACE7 lpDest,vector<BaseBullet* > enemyBulletList, vector<BaseEnemy* > EnemyList, vector<BaseTreasure* > TreasureList) {

	RECT		srcRect;
	RECT		destRect;
	HRESULT		hRet;

	CheckHit(enemyBulletList);
	CheckCollision(EnemyList);
	CheckHitTreasure(TreasureList);


	// Draw the shield status
	DDBLTFX     ddbltfx;
	
    ddbltfx.dwSize = sizeof( ddbltfx );
	ddbltfx.dwFillColor = RGB(30,5,15);

	if (HP < 350 )
		ddbltfx.dwFillColor = RGB(0,30,0);
	
	if (HP < 150 )
		ddbltfx.dwFillColor = RGB(8,4,0);	

	destRect.top = 30;
	destRect.left = 20;
	destRect.bottom = 45;
	destRect.right  = 20+HP/3;

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
					(*i)->draw( lpDest, 0, 0 );
			}

		}
	}

	char temp[10];
	sprintf(temp,"%d", HP);
	PlayerScore->bltText(temp,230,30);	
	PlayerScore->bltText("HP\0",20,10);

	sprintf(temp,"%d", power);
	PlayerScore->bltText("WEAPON POWER\0",20,55);
	PlayerScore->bltText(temp,240,54);	

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


void PlayerPlaneMode2::keyPresse( int key ) {

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

		presscnt++;
		if (state == 0)
		//	if ( !isShoot ) 
			if (presscnt > 30)
			{
				presscnt = 0;
				
				if ( !sound->IsPlaying() )
					sound->Play();

				isShoot = true;
				tempBullet = new PlayerBullet2;
				tempBullet->setMaxPower(power);

				if (power == 1)
				{
					tempBullet->setXY ( xPos + 60, yPos+5); 
					bulletList.push_back( tempBullet );
				}
				else if (power == 2)
				{
					tempBullet->setXY ( xPos + 60, yPos-4); 
					bulletList.push_back( tempBullet );
				}
				else
				{
					tempBullet->setXY ( xPos + 60, yPos-12); 
					bulletList.push_back( tempBullet );
				}
				
				tempBullet = NULL;
			}
		
		break;
	
	case DIK_X:
	
		if (state == 0)
		{
			if ( changecnt == 0)
			{
				change = true;			
			}			
			else
				change = false;			

			changecnt++;
		}
	

		break;

	

	}
} // The end of Method keyPressed

void PlayerPlaneMode2::keyRelease ( int key ) {
	
	changecnt = 0;
	change = false;
	isShoot = false;

} // The end of Method keyRelease


const void PlayerPlaneMode2::checkBoundary() {

	if ( xPos < 0 )
		xPos = 0;
	if ( xPos > 570 )
		xPos = 570;
	if ( yPos > 390 )
		yPos = 390;
	if ( yPos < 0 )
		yPos = 0;

} // The end of Method checkBoundary

const void PlayerPlaneMode2::updateFrame() {

	frame++;
	if ( frame > 7 )
		frame = 7;
	
	argXPos += 70;

	if ( argXPos >= 350 ) {

		argXPos = 0;
		argYPos += 70;

		if ( argYPos >= 350 ) {

			argYPos = 0;

		}

	}

} // The end of Method updateFrame

const void PlayerPlaneMode2::updateExplosionFrame() {

	explosionFrame++;
	if ( explosionFrame > 7 )
		explosionFrame = 7;

	argXPos += 70;

	if ( argXPos >= 490 ) {

		argXPos = 0;
		argYPos += 70;

		if ( argYPos >= 210 ) {

			argYPos = 0;

		}

	}

} // The end of Method updateExplosionFrame

vector<BaseBullet* > PlayerPlaneMode2::getBulletList() const {

	return bulletList;

} // The end of Method getBulletList

Score* PlayerPlaneMode2::getScorePt()
{
	return PlayerScore;
}


void PlayerPlaneMode2::setNextMode(BasePlayerPlane *p)
{
	NextMode = p;
}


bool PlayerPlaneMode2::changeNextMode()
{
	Transform();
	return change;
}


BasePlayerPlane* PlayerPlaneMode2::getNextMode()
{
	return NextMode;
}


void PlayerPlaneMode2::Transform()
{
	if (change)
	{
		NextMode->setXY(xPos,yPos);
		NextMode->getScorePt()->setscore(PlayerScore->getscore());
		NextMode->setBulletList(bulletList);
		NextMode->setStrength (HP);
		NextMode->setstate(0);
	}
}

void PlayerPlaneMode2::setBulletList(vector<BaseBullet* > it)
{
	bulletList = it;

}

bool PlayerPlaneMode2::CheckHit( vector<BaseBullet* >& enemybulletList) 
{
	bool hit=false;
	int count=0;

	for (vector<BaseBullet* >::iterator i=enemybulletList.begin(); i!=enemybulletList.end(); i++) 
	{

		if (*i != NULL)
		{
			if ( (*i)->getXPos() + (*i)->getWidth() > getXPos() && // top-rigth
				(*i)->getXPos() < getXPos() + getWidth()      && // top-left
				(*i)->getYPos() + (*i)->getHeight() > getYPos()     && // bottom-left
			 	(*i)->getYPos() < getYPos()+getHeight() -10 )        // bottom-
			{
				speed = 4;

				if (--power < 1 )
					power = 1;

				setStrength( HP-(*i)->getPower() );
 
				if (HP <= 0 )
				{
					HP = 0;
					state = 1;
				}

				(*i)->setPower ( (*i)->getPower() -10);
		//		(*i)->setPower ( 0 );
				
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


bool PlayerPlaneMode2::CheckCollision(vector<BaseEnemy* > &EnemyList)
{
	bool collide=false;
	
	
	for (vector<BaseEnemy* >::iterator i=EnemyList.begin(); i!=EnemyList.end(); i++) 
	{
	
		if ((*i != NULL) && (*i)->getappear())
		{
			if ( (*i)->getXPos() + (*i)->getWidth() > getXPos() && // top-rigth
				(*i)->getXPos() < getXPos() + getWidth()      && // top-left
				(*i)->getYPos() + (*i)->getHeight() -25> getYPos()     && // bottom-left
			 	(*i)->getYPos() +25 < getYPos()+getHeight()/2)        // bottom-
			{
				speed = 4;

				if (--power < 1 )
					power = 1;

				setStrength( HP-1 );

				if (HP <=0 )
				{
					HP = 0;
					state = 1;
				}
		
				if ( !explosion->IsPlaying() )
					explosion->Play();
			
				collide = true;

			}
		}
	
	}

	return collide;
}

bool PlayerPlaneMode2::CheckHitTreasure( vector<BaseTreasure*> & TreasureList)
{
	bool hit=false;
	int count=0;
	
	for (vector<BaseTreasure* >::iterator i=TreasureList.begin(); i!=TreasureList.end(); i++) 
	{
	
		if (*i != NULL)
		{
			if ( (*i)->getXPos() + 25 > getXPos() && // top-rigth
				(*i)->getXPos() < getXPos() + getWidth()    && // top-left
				(*i)->getYPos() + 25 > getYPos()     && // bottom-left
			 	(*i)->getYPos() < getYPos()+getHeight() )        // bottom-
			{
				if ( !getT->IsPlaying() )
					getT->Play();

				switch ( (*i)->getType() )
				{
					case 1:
						HP += 50;
						if (HP > 600)
							HP =600;
						break;
					case 2:
						UpPower();
						break;
					case 3:				
						PlayerScore->addscore(10000);					
						break;
					case 4:
						UpPower();						
						NextMode->UpPower();
						break;
					case 5:
						speed++;
						break;
					default:
						break;

				}
	
				(*i)->setDestroy();		
				
				hit = true;

			}
		}
	
	}

	return hit;
}

int PlayerPlaneMode2::getWidth() const {

		return width;

} // The end of Method getWidth

int PlayerPlaneMode2::getHeight() const {

		return height;

} // The end of Method getHeight


void PlayerPlaneMode2::setstate(int ns)
{
	state = ns;
}


void PlayerPlaneMode2::UpPower() 
{
	if (++power > 3)
		power = 3;
}


void PlayerPlaneMode2::Accept(BaseVisitor &v)
{
	v.VisitPlayer(this);
}

bool PlayerPlaneMode2::getChange()
{
	return change;
}