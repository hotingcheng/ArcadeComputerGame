#ifndef BaseTreasure_H
#define BaseTreasure_H


#include "resource.h"
#include "GraphicsLayer.h"


class BaseTreasure {

	private:

		int	xPos;
		int yPos;
		RECT	rcLastPos;
		int iType;	// 1 -- increase HP ; 2 -- increase weapon power

		LPDIRECTDRAWSURFACE7     lpDDNormal;

	public:

		int		frame;
		
		BaseTreasure();
		~BaseTreasure();
		
		int getType() const;
		const void setType( const int );
		
		const void setXY( const int, const int );
		int getXPos() const;
		int getYPos() const;
		
		const void move( int );

		bool draw(LPDIRECTDRAWSURFACE7 );

		
}; // The end of Class BaseTreasure

#endif