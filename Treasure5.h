#ifndef Treasure5_H
#define Treasure5_H

#include "BaseTreasure.h"

class Treasure5 : public BaseTreasure
{
	protected:
		virtual const void checkBoundary();
	public:

//		Treasure5(Treasure5&);
		Treasure5();
		~Treasure5();
		
		virtual int getType() const;
		virtual const void setType( const int );
		
		virtual const void setXY( const int, const int );
		virtual int getXPos() const;
		virtual int getYPos() const;
		
		virtual const void move( int );
		virtual void setDestroy();
		virtual int getDestroy();
				
		virtual bool draw(LPDIRECTDRAWSURFACE7 );

		
}; // The end of Class Treasure

#endif