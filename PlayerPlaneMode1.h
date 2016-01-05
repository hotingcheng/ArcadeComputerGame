#ifndef PLAYERPLANEMODE1_H
#define PLAYERPLANEMODE1_H

#include "BasePlayerPlane.h"

class PlayerPlaneMode1: public BasePlayerPlane
{
private:
	virtual void Transform();
	
public:

	virtual bool CheckCollision(vector<BaseEnemy* > &);
	virtual bool CheckHit( vector<BaseBullet* > &) ;
	virtual bool CheckHitTreasure(vector<BaseTreasure* > &);

	PlayerPlaneMode1();
	~PlayerPlaneMode1();

	virtual int getWidth() const;
	virtual int getHeight() const;
	
	virtual const void setStrength( const int );
	virtual int getStrength() const;
	
	virtual const void setSpeed( const int );
	virtual int getSpeed() const;

	virtual const void setXY( const int, const int );
	virtual int getXPos() const;
	virtual int getYPos() const;
	
	virtual bool isExploding() const;
	virtual bool isDestroyMe() const;

	virtual void UpPower() ;
//	virtual const void getState() const;
//	virtual int setState( int );

	virtual vector<BaseBullet* > getBulletList() const;

	virtual HRESULT draw(LPDIRECTDRAWSURFACE7 , vector<BaseBullet* >, vector<BaseEnemy* >, vector<BaseTreasure* >);
//	virtual HRESULT draw(LPDIRECTDRAWSURFACE7 , vector<BaseBullet* >);
//	virtual HRESULT draw(LPDIRECTDRAWSURFACE7 );

	virtual void keyPresse( int );
	virtual void keyRelease( int );

	virtual const void checkBoundary();

	// To update the frame so that the object seems more dynamic
	virtual const void updateFrame();
	virtual const void updateExplosionFrame();

	virtual Score * getScorePt();

	virtual void setNextMode(BasePlayerPlane*);

	virtual bool changeNextMode();
	virtual BasePlayerPlane* getNextMode();
	virtual void setBulletList(vector<BaseBullet* > );

	virtual void setstate(int);

	virtual void Accept(BaseVisitor &v);

	virtual bool getChange();
	
};

#endif