#ifndef TREASURE2_H
#define TREASURE2_H

#include "BaseTreasure.h"

class Treasure2 : public BaseTreasure
{
	protected:
		virtual const void checkBoundary();

	public:

//		Treasure2(Treasure2&);
		Treasure2();
		~Treasure2();
		
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