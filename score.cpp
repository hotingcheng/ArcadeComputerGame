#include "Score.h"

Score::Score()
{
	score = 0;

	lpAlpha = Graphics()->DDLoadBitmap ( Graphics()->getDirectDraw(), 
									   MAKEINTRESOURCE(IDB_letter), 
									   0, 0 );
	
	if ( lpAlpha == NULL )
		throw GameError("Error in DDLoadBitmap of Score");

	HRESULT ddrval = Graphics()->DDSetColorKey( lpAlpha, CLR_INVALID );

	if ( ddrval!= DD_OK )
		throw GameError("Error in DDSetColorKey" );
}

Score::~Score()
{
	SafeRelease(lpAlpha);
}

void Score::addscore(int add)
{
	score += add;
}

unsigned int Score::getscore()
{
	return score;
}

void Score::bltText(char*  buffer, int  x, int y)
{
	
	// Draw text to the screen

	int		pos;
	int		nextx;
	RECT	rcRect;
	HRESULT hRet;

	nextx = x;
	while (*buffer != '\0')
	{
		if (*buffer != ' ')
		{
			if (*buffer >= 48 &&
				*buffer <= 57)
				pos = (int) *buffer - 48;
			else
				pos = (int) *buffer - 55;
			if (*buffer == '@')
				pos = 36;
			if (*buffer == '-')
				pos = 37;
			if (*buffer == ',')
				pos = 38;
			if (*buffer == '.')
				pos = 39;

			rcRect.left = AA[pos].start;
			rcRect.right = AA[pos].end;
			rcRect.top = 0;
			rcRect.bottom = 15;

			while (1)
			{
				hRet = Graphics()->getBackBuffer()->BltFast(nextx, y, lpAlpha, &rcRect, TRUE);
				if (hRet == DD_OK)
				{
					break;
				}
				if (hRet == DDERR_SURFACELOST)
				{
//					hRet = RestoreSurfaces();
//					if (hRet != DD_OK)
//						break;
				}
				if (hRet != DDERR_WASSTILLDRAWING)
					break;
			}

//			Graphics()->flip();
			nextx += (AA[pos].end - AA[pos].start) + 1;
		}
		else
			nextx += 15;

		buffer++;
	}

}
		
void Score::DrawScore(int x, int y)
{
	char				scorebuf[9];
    unsigned int        rem;

    // blt everything in reverse order if we are doing destination transparency
    // calculate score string
    scorebuf[0] = score/10000000 + '0';
    rem = score % 10000000;
    scorebuf[1] = rem/1000000 + '0';
    rem = score % 1000000;
    scorebuf[2] = rem/100000 + '0';
    rem = score % 100000;
    scorebuf[3] = rem/10000 + '0';
    rem = score % 10000;
    scorebuf[4] = rem/1000 + '0';
    rem = score % 1000;
    scorebuf[5] = rem/100 + '0';
    rem = score % 100;
    scorebuf[6] = rem/10 + '0';
    rem = score % 10;
    scorebuf[7] = rem + '0';
	scorebuf[8] = '\0';
	bltText(scorebuf, x, y);
}

void Score::setscore(unsigned int newscore)
{
	score = newscore;
}