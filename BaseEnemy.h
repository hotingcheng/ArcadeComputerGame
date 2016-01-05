#ifndef BASEENEMY_H
#define BASEENEMY_H

#include <vector>
using namespace std;

#include "resource.h"
#include "Sound.h"

#include "Strategy.h"
#include "Strategy1.h"
#include "Strategy2_1.h"
#include "Strategy2_2.h"
#include "Strategy3.h"
#include "Strategy4.h"
#include "Strategy_Enemy.h"

#include "BaseBullet.h"
#include "EnemyBaseBullet.h"
#include "EnemyBullet1.h"
#include "EnemyBullet2.h"
#include "EnemyBullet3.h"
#include "EnemyBullet4.h"
#include "EnemyBullet5.h"
#include "EnemyBullet6.h"
#include "EnemyBullet7.h"
#include "EnemyBullet8.h"
#include "BigBossAttack.h"

#include "BaseTreasure.h"
#include "Treasure1.h"
#include "Treasure2.h"
#include "Treasure3.h"
#include "Treasure4.h"
#include "Treasure5.h"

#include "PlayerBaseBullet.h"
#include "Score.h"

#include "BaseVisitor.h"

class BaseEnemy : public Strategy_Enemy
{

	protected:

		int transform;

		bool   appear;
		int	   point;
		int	   timeAppear;

		int    xPos;
		int    yPos;

		int	   width;
		int    height;
		int	   argXPos;
		int	   argYPos;

		int    speed;
		int	   strength;

		// Store the normal frame number, start from 1
		int	   frame;
		// Store the explosion frame number, start from 2
		int	   explosionFrame;

		// 0 - normal state
		// 0 - explosion state
		int	   state;

		int	   iQtdeDown;
		int	   amDown;
		
		int	   iStr;
		int	   iType;
		int	   iExtra;	

		LPDIRECTDRAWSURFACE7     lpDDNormal;
		LPDIRECTDRAWSURFACE7     lpDDExplosion;

		BaseEnemy*   next;
		Strategy*	S;
		BaseBullet* tempBullet;

		cSound *explosion;

		BaseTreasure* Trea;


	public:
		virtual bool CheckHit(vector<BaseBullet*>)=0;

		virtual int getTimeAppear()=0;
		
	//DWORD  dwLastShoot;
		BaseEnemy() {};
		BaseEnemy( int time ){};	// Constructor
		BaseEnemy( int time , int level){};	// Constructor
		~BaseEnemy() {};	// Destructor

		virtual int getStr() const=0; 
		virtual const void setStr( const int )=0;
		virtual const void lowStr( const int )=0;
		virtual const void setQtdeDown( const int )=0;
	
		virtual BaseTreasure* createTreasure( const int )=0;
		virtual int getTreasure() const=0;
			
		virtual const void setAmDown( const int )=0;
		virtual int getAmDown() const=0;
	
		virtual const void setStrength( const int )=0;
		virtual int getStrength() const=0;
		
		virtual const void setSpeed( const int )=0;
		virtual int getSpeed() const=0;
	

		virtual const void setXY( const int, const int )=0;
		virtual int getXPos() const=0;
		virtual int getYPos() const=0;

		virtual int getWidth() const=0;
		virtual int getHeight() const=0;
		
		virtual BaseEnemy* getNext() const=0;
		virtual const void setNext( BaseEnemy* )=0;
	
		virtual int getState() const=0;
		virtual const void setState( const int )=0;
	
		virtual int move( const int )=0;
	
		// Return true if the enemy is explosing
		virtual bool isExploding() const=0;
		
		// Return true if the enemy create extra when destroyed
		virtual bool isDropExtra() const=0;

		// Return true if all the explosion frame is displayed
		virtual bool isDestroyMe() const=0;
	
		virtual HRESULT draw(LPDIRECTDRAWSURFACE7 )=0;

		virtual const void checkBoundary()=0;

		virtual const void updateFrame()=0;
		virtual const void updateExplosionFrame()=0;

		virtual BaseBullet* Attack()=0;
		
		virtual Strategy* getStrategy()=0;
		virtual int getpoint()=0;

		virtual void setappear()=0;
		virtual bool getappear()=0;

		virtual void Accept(BaseVisitor &v){ v.VisitEnemy(this); };

}; // The end of Class BaseEnemy

#endif