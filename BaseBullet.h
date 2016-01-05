#ifndef BULLET_H
#define BULLET_H

#include "resource.h"
#include "Sound.h"
#include "GameError.h"
#include "GraphicsLayer.h"

#include "BaseVisitor.h"

class BaseBullet {

	protected:

		int	xPos;
		int yPos;

		int width;
		int height;
		
		int iType;

		// Store the normal frame number, start from 1
		int frame;

		int speed;
		int power;

		// 0 -- appear
		// 1 -- destroy
		int isDestroy;

		LPDIRECTDRAWSURFACE7     lpDDNormal;

				
	public:

		BaseBullet();	// Constructor
		~BaseBullet();	// Destructor
	
		virtual int getType() const=0;
		virtual const void setType( const int )=0;
	
		virtual const void setXY(int newx, int newy)=0;
		virtual int getXPos() const=0;
		virtual int getYPos() const=0;

		virtual int getWidth() const=0;
		virtual int getHeight() const=0;
	
		virtual const void setPower( int newp )=0;
		virtual const void setMaxPower( int ){};
		virtual int getPower() const=0;

		virtual const void setDestroy( const int )=0;
		virtual int getDestroy() const=0;

		// This method is called at the end of the draw method
		virtual const void move(int,int)=0;
		
		virtual bool draw( LPDIRECTDRAWSURFACE7, int, int )=0;

		virtual const void checkDestroy()=0;
		virtual void trackplayerposition()=0;

		virtual void Accept(BaseVisitor &v){ v.VisitBullet(this); };
		
}; // The end of Class BaseBullet

#endif