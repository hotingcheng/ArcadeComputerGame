#ifndef TESTPLAYER_H
#define TESTPLAYER_H


#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/extensions/HelperMacros.h>
#include <assert.h>

#include <vector>
using namespace std;

#include "BaseBullet.h"
#include "BaseTreasure.h"
#include "Treasure1.h"
#include "BasePlayerPlane.h"
#include "PlayerPlaneMode1.h"
#include "Enemy1.h"


using namespace CppUnit;

class TestPlayer : public CppUnit::TestCase  
{

  //CPPUNIT_TEST_SUITE( CsimpeTestCircle );
  //CPPUNIT_TEST( testRect );
  //CPPUNIT_TEST ( testBounce );
  //CPPUNIT_TEST_SUITE_END();

private:

	BasePlayerPlane *player;

public:
	
	TestPlayer();
	virtual ~TestPlayer();

	void runTest();

	/*
	 *	The use case one	
	 */
	// Test the movement of player
	void testMove();

	/*
	 *	The use case two
	 */
	// Test the case of getting score treasure
	void testDestoryEnemy();

	// Test the case of getting power treasure
	void testGetPowerTreasure();

	/*
	 * The use case three
	 */
	// Test the being attack of player 
	void testAttacked();
	
	// Test the case of collision
	void testCollision();

	/*
	 *	The use case four
	 */
	// Test the change mode of player
	void testChangeMode();

	static Test *suite ()
	{
		TestSuite *suiteofTests = new TestSuite;
		suiteofTests->addTest (new TestCaller <TestPlayer>("testMove", testMove));
		suiteofTests->addTest (new TestCaller <TestPlayer>("testAttacked", testAttacked));
		suiteofTests->addTest (new TestCaller <TestPlayer>("testChangeMode", testChangeMode));
		suiteofTests->addTest (new TestCaller <TestPlayer>("testGetPowerTreasure", testGetPowerTreasure));
		suiteofTests->addTest (new TestCaller <TestPlayer>("testDestoryEnemy", testDestoryEnemy));
		suiteofTests->addTest (new TestCaller <TestPlayer>("testCollision", testCollision));
		return suiteofTests;
	};


	
};

#endif 
