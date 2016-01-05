#ifndef Leader2_H
#define Leader2_H

#include <vector>
using namespace std;

#include "BaseEnemy.h"

class Leader2 : public BaseEnemy
{
	public:
		virtual bool CheckHit(vector<BaseBullet*>);

		virtual int getTimeAppear();
		
	//DWORD  dwLastShoot;
		Leader2( int time, int );	// Constructor
		~Leader2();	// Destructor

		virtual int getStr() const; 
		virtual const void setStr( const int );
		virtual const void lowStr( const int );
		virtual const void setQtdeDown( const int );
	
		virtual BaseTreasure* createTreasure( const int );
		virtual int getTreasure() const;
			
		virtual const void setAmDown( const int );
		virtual int getAmDown() const;
	
		virtual const void setStrength( const int );
		virtual int getStrength() const;
		
		virtual const void setSpeed( const int );
		virtual int getSpeed() const;
	

		virtual const void setXY( const int, const int );
		virtual int getXPos() const;
		virtual int getYPos() const;

		virtual int getWidth() const;
		virtual int getHeight() const;
		
		virtual BaseEnemy* getNext() const;
		virtual const void setNext( BaseEnemy* );
	
		virtual int getState() const;
		virtual const void setState( const int );
	
		virtual int move( const int );
	
		// Return true if the enemy is explosing
		virtual bool isExploding() const;
		
		// Return true if the enemy create extra when destroyed
		virtual bool isDropExtra() const;

		// Return true if all the explosion frame is displayed
		virtual bool isDestroyMe() const;
	
		virtual HRESULT draw(LPDIRECTDRAWSURFACE7 );

		virtual const void checkBoundary();

		virtual const void updateFrame();
		virtual const void updateExplosionFrame();

		virtual BaseBullet* Attack();
		
		virtual Strategy* getStrategy();
		virtual int getpoint();

		virtual void setappear();
		virtual bool getappear();
	
}; // The end of Class BaseEnemy

#endif