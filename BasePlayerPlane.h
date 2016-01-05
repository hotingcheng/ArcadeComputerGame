#ifndef BASEPLAYERPLANE_H
#define BASEPLAYERPLANE_H

#include <vector>
#include <string>
using namespace std;

#include "BaseEnemy.h"

#include "BaseBullet.h"
#include "PlayerBaseBullet.h"
#include "PlayerBullet1.h"
#include "PlayerBullet2.h"

#include "PlayerBaseBullet.h"
#include "BaseBullet.h"

#include "resource.h"
#include "Sound.h"
#include "InputLayer.h"
#include "Score.h"

#include "BaseVisitor.h"

typedef vector< BaseBullet* >::iterator literator;

class BasePlayerPlane: public iKeyboardReceiver {

	protected:

		int presscnt;
		int power;

		int	   width;
		int	   height;
		int	   changecnt;
		int    xPos;
		int    yPos;
		int	   argXPos;
		int	   argYPos;

		int    speed;
		int	   HP;

		bool isShoot;
	//	bool isChange;

		bool change;

		// 0 - normal state
		// 1 - explosion state
		int    state;
		
		// Store the normal fram number, start from 1
		int frame;
		// Store the explosion frame number, start from 1
		int explosionFrame;


		vector<BaseBullet* > bulletList;
		BaseBullet* tempBullet;

		LPDIRECTDRAWSURFACE7     lpDDNormal;
		LPDIRECTDRAWSURFACE7     lpDDExplosion;

		Score *PlayerScore;

		cSound *sound;

		BasePlayerPlane *NextMode;

		cSound *explosion;
		cSound *getT;

		virtual void Transform()=0;
		

	public:

		virtual bool CheckCollision(vector<BaseEnemy* > &)=0;
		virtual bool CheckHit(vector<BaseBullet* > &)=0;
		
		virtual bool CheckHitTreasure(vector<BaseTreasure* > &)=0;

		BasePlayerPlane() {};	// Constructor
		virtual ~BasePlayerPlane() {};	// Destructor

		virtual const void setStrength( const int )=0;
		virtual int getStrength() const=0;
		
		virtual const void setSpeed( const int )=0;
		virtual int getSpeed() const=0;
	
		virtual const void setXY( const int, const int )=0;
		virtual int getXPos() const=0;
		virtual int getYPos() const=0;
		
		virtual bool isExploding() const=0;
		virtual bool isDestroyMe() const=0;

		virtual int getWidth() const=0;
		virtual int getHeight() const=0;
	
		virtual void UpPower() =0;
	//	virtual const void getState() const;
	//	virtual int setState( int );

		virtual vector<BaseBullet* > getBulletList() const=0;

		virtual HRESULT draw(LPDIRECTDRAWSURFACE7 , vector<BaseBullet* >, vector<BaseEnemy* >, vector<BaseTreasure* >)=0;
//		virtual HRESULT draw(LPDIRECTDRAWSURFACE7 , vector<BaseBullet* >)=0;
//		virtual HRESULT draw(LPDIRECTDRAWSURFACE7 )=0;

		virtual void keyPresse( int )=0;
		virtual void keyRelease( int )=0;

		virtual const void checkBoundary()=0;

		// To update the frame so that the object seems more dynamic
		virtual const void updateFrame()=0;
		virtual const void updateExplosionFrame()=0;

		virtual Score * getScorePt()=0;

		virtual void setNextMode(BasePlayerPlane *)=0;
		
		virtual bool changeNextMode()=0;
		virtual BasePlayerPlane* getNextMode()=0;

		virtual void setBulletList(vector<BaseBullet* > )=0;

		virtual void setstate(int)=0;

		virtual void Accept(BaseVisitor &v)=0;

		virtual bool getChange() = 0;

}; // The end of Class BasePlayerPlane


#endif