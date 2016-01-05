#include "TestPlayer.h"

TestPlayer::TestPlayer() {

	player = new PlayerPlaneMode1;


} // The end of Constructor

TestPlayer::~TestPlayer() {

	if ( player )
		delete player;
	player = NULL;

} // The end of Destructor

void TestPlayer::runTest() {

} // The end of runTest

void TestPlayer::testMove() {

	int yPos = player->getYPos();
	player->keyPresse( DIK_UP );
	player->keyRelease( DIK_UP );
	int newYPos = player->getYPos();
	assert ( newYPos < yPos );

	int xPos = player->getXPos();
	player->keyPresse( DIK_RIGHT );
	player->keyRelease( DIK_RIGHT );
	int newXPos = player->getXPos();

	assert ( newXPos > xPos );

} // The end of testMove

void TestPlayer::testChangeMode() {

	int oldSpeed = player->getSpeed();
	player->setstate( 0 );
	assert( oldSpeed == 8 );

	player->keyPresse( DIK_X );
	assert ( player->getChange() );
	
	player->keyRelease( DIK_X );

} // The end of Method testChangeMode

void TestPlayer::testAttacked() {

	BaseBullet *enemyBullet = new EnemyBullet1;
	enemyBullet->setXY( 10, 10 );
	vector< BaseBullet* > bulletList;
	bulletList.push_back( enemyBullet );
	assert( !bulletList.empty() );
	
	int enemyPower = enemyBullet->getPower();
	enemyBullet = NULL;
	
	player->setXY( 10, 10 );
	player->setstate( 0 );
	
	int oldStrength = player->getStrength();
	
	assert ( player->CheckHit( bulletList ) );

	int newStrength = player->getStrength();
	oldStrength -= enemyPower;
	assert ( oldStrength == newStrength );
	
	literator i = bulletList.begin();
	delete *i;
	bulletList.clear();

} // The end of Method testAttacked

void TestPlayer::testGetPowerTreasure() {

	BaseTreasure *treasure = new Treasure2;
	treasure->setXY( 10, 10 );
	assert ( treasure->getType() == 2 );
	vector< BaseTreasure* > treasureList;
	treasureList.push_back( treasure );
	treasure = NULL;
	
	player->setXY( 10, 10 );
	assert ( player->CheckHitTreasure( treasureList ) );

	vector< BaseTreasure* >::iterator i;
	i = treasureList.begin();
	delete *i;
	treasureList.clear();

} // The end of Method testGetPowerTreasure

void TestPlayer::testDestoryEnemy() {

	player->setXY( 100, 100 );
	player->setstate( 0 );

	vector< BaseBullet* > oldBulletList = player->getBulletList();
	assert( oldBulletList.empty() );

	player->keyPresse( DIK_SPACE );
	player->keyRelease( DIK_SPACE );

	vector< BaseBullet* > newBulletList = player->getBulletList();
	
	assert( !newBulletList.empty() );

	vector<BaseBullet* >::iterator i = newBulletList.begin();
	
	assert( (*i) );
	
	(*i)->setXY( 10, 10 );
	
	BaseEnemy *enemy = new Enemy1( 0, 1 );
	enemy->setXY( 10, 10 );
	enemy->setStrength( 1 );
	
	assert( enemy->CheckHit( newBulletList ) );
	assert( enemy->getState() == 1 );

	int temp = player->getScorePt()->getscore();

	if ( enemy->getState() == 1 )
		player->getScorePt()->addscore( enemy->getpoint() );

	assert( temp < player->getScorePt()->getscore() );

//	vector<BaseBullet* >::iterator j = newBulletList.begin();
//	delete *j;
//	newBulletList.empty();

	delete enemy;

} // The end of Method testDestoryEnemy

void TestPlayer::testCollision() {

	BaseEnemy *enemy = new Enemy1( 1, 1 );
	enemy->setappear();
	enemy->setXY( 10, 10 );
	vector< BaseEnemy* > enemyList;
	enemyList.push_back( enemy );
	enemy = NULL;
	
	player->setXY( 10, 10 );
	assert ( player->CheckCollision( enemyList ) );

	vector<BaseEnemy* >::iterator i = enemyList.begin();
	delete *i;
	enemyList.clear();

} // The end of Method testCollision