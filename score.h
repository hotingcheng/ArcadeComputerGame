#ifndef SCORE_H
#define SCORE_H

#include "Alpha.h"
#include "GraphicsLayer.h"
#include "resource.h"
#include "BaseVisitor.h"

class Score
{
protected:
	unsigned int score;
	LPDIRECTDRAWSURFACE7 lpAlpha;
public:
	Score();
	~Score();
	virtual void addscore(int);
	virtual void setscore(unsigned int);
	virtual unsigned int getscore();
	virtual void bltText(char*  buffer, int  x, int y);
	virtual void DrawScore(int x, int y);

	virtual void Accept(BaseVisitor &v){ v.VisitScore(this); };
};

#endif