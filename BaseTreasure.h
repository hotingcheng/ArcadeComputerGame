#ifndef BASETREASURE_H
#define BASETREASURE_H


#include "resource.h"
#include "GraphicsLayer.h"

#include "BaseVisitor.h"

class BaseTreasure {

	protected:

		int Destroy;
		int	frame;
		int	xPos;
		int yPos;
		RECT	rcLastPos;
		int iType;	
	
		LPDIRECTDRAWSURFACE7     lpDDNormal;

		virtual const void checkBoundary()=0;

	public:

//		BaseTreasure(BaseTreasure&){};
		BaseTreasure(){};
		~BaseTreasure(){};
		
		virtual int getType() const=0;
		virtual const void setType( const int )=0;
		
		virtual const void setXY( const int, const int )=0;
		virtual int getXPos() const=0;
		virtual int getYPos() const=0;
		
		virtual const void move( int )=0;
		virtual void setDestroy()=0;
		virtual int getDestroy()=0;
		
		virtual bool draw(LPDIRECTDRAWSURFACE7 )=0;
	
		virtual void Accept(BaseVisitor &v){ v.VisitTreasure(this); };

		
}; // The end of Class Treasure

#endif