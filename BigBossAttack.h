#ifndef BigBossAttack_H
#define BigBossAttack_H

#include "EnemyBaseBullet.h"

class BigBossAttack : public EnemyBaseBullet
{
	public:

		BigBossAttack();	// Constructor
		~BigBossAttack();	// Destructor
	
		virtual int getType() const;
		virtual const void setType( const int );
	
		virtual const void setXY(int newx, int newy);
		virtual int getXPos() const;
		virtual int getYPos() const;

		virtual int getWidth() const;
		virtual int getHeight() const;
	
		virtual const void setPower( int newp );
		virtual int getPower() const;

		virtual const void setDestroy( const int );
		virtual int getDestroy() const;

		// This method is called at the end of the draw method
		virtual const void move(int,int);
		
		virtual bool draw( LPDIRECTDRAWSURFACE7,int ,int  );

		virtual const void checkDestroy();

		virtual void trackplayerposition();
		
}; // The end of Class BaseBullet

#endif