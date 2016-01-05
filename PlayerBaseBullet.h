#ifndef PLAYERBASEBULLET_H
#define PLAYERBASEBULLET_H

#include "BaseBullet.h"

class PlayerBaseBullet : public BaseBullet
{
	public:

		PlayerBaseBullet(){};	// Constructor
		~PlayerBaseBullet(){};	// Destructor
	
		virtual int getType() const=0;
		virtual const void setType( const int )=0;
	
		virtual const void setXY(int newx, int newy)=0;
		virtual int getXPos() const=0;
		virtual int getYPos() const=0;

		virtual int getWidth() const=0;
		virtual int getHeight() const=0;
	
		virtual const void setPower( int newp )=0;
		virtual const void setMaxPower( int  )=0;
		virtual int getPower() const=0;

		virtual const void setDestroy( const int )=0;
		virtual int getDestroy() const=0;

		// This method is called at the end of the draw method
		virtual const void move(int,int)=0;
		
		virtual bool draw( LPDIRECTDRAWSURFACE7, int, int )=0;

		virtual const void checkDestroy()=0;

		virtual void trackplayerposition(){};

		
}; // The end of Class BaseBullet

#endif