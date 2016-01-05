#ifndef TREASURE3_H
#define TREASURE3_H

#include "BaseTreasure.h"

class Treasure3 : public BaseTreasure
{
	protected:
		virtual const void checkBoundary();
	public:

//		Treasure3(Treasure3&);
		Treasure3();
		~Treasure3();
		
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