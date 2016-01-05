#ifndef EnemyBullet5_H
#define EnemyBullet5_H

#include "EnemyBaseBullet.h"

class EnemyBullet5 : public EnemyBaseBullet
{
	public:

		EnemyBullet5();	// Constructor
		~EnemyBullet5();	// Destructor
	
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