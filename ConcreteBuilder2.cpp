#include "ConcreteBuilder2.h"

ConcreteBuilder2::ConcreteBuilder2()
{
	EnemyContainer.clear();
}

vector<BaseEnemy *> ConcreteBuilder2::getstage(int stage)
{
	if (stage == 1)
	{
		buildstage1();
		return EnemyContainer;
	}
	else if (stage == 2)
	{
		buildstage2();
		return EnemyContainer;
	}
	else if (stage == 3)
	{	
		buildstage3();
		return EnemyContainer;
	}
	else
		return NULL;

}

void ConcreteBuilder2::buildstage1()
{

	EnemyContainer.clear();


	for ( int i = 0; i < 10; i++ ) 
		EnemyContainer.push_back( new Enemy1( (i+5) * 1000 , 2) );	

	for ( i=10; i<30; i++)
	{
		EnemyContainer.push_back( new Enemy2( (i+5) * 1000, 2 ) );	
		EnemyContainer.push_back( new Enemy3( (i+5) * 1000, 2 ) );	
		if (i%4==0)
			EnemyContainer.push_back( new Leader2( (i+5) * 1000, 2 ) );	
	}

	EnemyContainer.push_back( new Leader1( (35) * 1000, 2 ) );	

	for (i = 40; i<46; i++)
	{
		EnemyContainer.push_back( new Leader2( (i+5) * 1000 , 2) );	
		
		if (i%2==0)
			EnemyContainer.push_back( new Leader1( (i+5) * 1000 , 2) );			
	}

	for ( i=42; i<50; i++)
	{
		if (i%3==0)
		{
			EnemyContainer.push_back( new Enemy1( (i+5) * 1000 , 1) );	
			EnemyContainer.push_back( new Enemy2( (i+6) * 1000, 1 ) );	
			EnemyContainer.push_back( new Enemy3( (i+7) * 1000, 1 ) );	
		}
		
		if (i%6==0)
			EnemyContainer.push_back( new Leader2( (i+5) * 1000, 2 ) );	
	}

	for (i = 46; i<60; i++)
	{
		EnemyContainer.push_back( new Enemy4( (i+5) * 1000 , 2) );	
		EnemyContainer.push_back( new Enemy4_2( (i+5) * 1000 , 2) );	
	}

	EnemyContainer.push_back( new BigBoss1( (70) * 1000 ,2 ) );	

}


void ConcreteBuilder2::buildstage2()
{
	EnemyContainer.clear();

	for ( int i = 5; i<60; i++)
	{
		EnemyContainer.push_back( new Enemy4( (i+5) * 1000 , 2) );	
		EnemyContainer.push_back( new Enemy4_2( (i+5) * 1000 , 2) );	
	}


	for ( i = 1; i < 20; i++ ) 
		EnemyContainer.push_back( new Enemy1( (i+5) * 1000 , 3) );	

	for ( i=10; i<30; i++)
	{
		EnemyContainer.push_back( new Enemy2( (i+5) * 1000, 2 ) );	
		EnemyContainer.push_back( new Enemy3( (i+5) * 1000, 2 ) );	
		if (i%4==0)
			EnemyContainer.push_back( new Leader2( (i+5) * 1000, 2 ) );	
	}

	EnemyContainer.push_back( new Leader1( (35) * 1000, 3 ) );	

	for (i = 40; i<43; i++)
	{
		EnemyContainer.push_back( new Leader2( (i+5) * 1000 , 3) );	
		
		if (i%2==0)
			EnemyContainer.push_back( new Leader1( (i+5) * 1000 , 3) );			
	}

	for ( i=46; i<50; i++)
	{
		EnemyContainer.push_back( new Enemy2( (i+5) * 1000, 2 ) );	
		EnemyContainer.push_back( new Enemy3( (i+5) * 1000, 2 ) );	
		
		if (i%4==0)		
			EnemyContainer.push_back( new Leader2( (i+5) * 1000, 3 ) );	
		
		if (i%3==0)		
			EnemyContainer.push_back( new Leader1( (i+5) * 1000, 3 ) );	
	}


	EnemyContainer.push_back( new BigBoss1( (60) * 1000 ,3 ) );	

		
}




void ConcreteBuilder2::buildstage3()
{
	EnemyContainer.clear();

	for ( int i = 5; i<70; i++)
	{
		EnemyContainer.push_back( new Enemy4( (i+5) * 1000 , 3) );	
		EnemyContainer.push_back( new Enemy4( (i+5) * 1000 , 3) );
		EnemyContainer.push_back( new Enemy4_2( (i+5) * 1000 , 3) );	
		EnemyContainer.push_back( new Enemy4_2( (i+5) * 1000 , 3) );	
	}


	for ( i = 0; i<20; i++)
	{
		EnemyContainer.push_back( new Enemy2( (i+5) * 1000 , 2) );	
//		EnemyContainer.push_back( new Enemy3( (i+5) * 1000, 2 ) );	
	}

	for ( i = 21; i < 40; i++ ) 
		EnemyContainer.push_back( new Enemy1( (i+5) * 1000 , 2) );	

	for ( i=10; i<30; i++)
	{
		if (i%6==0)
			EnemyContainer.push_back( new Enemy3( (i+5) * 1000, 2 ) );	
//		EnemyContainer.push_back( new Enemy4( (i+5) * 1000, 2 ) );	
//		EnemyContainer.push_back( new Enemy4( (i+5) * 1000, 2 ) );	
		if (i%7==0)
			EnemyContainer.push_back( new Leader2( (i+5) * 1000, 2 ) );	
	}

  	for ( i=35; i<40; i++)
	{
		EnemyContainer.push_back( new Enemy2( (i+5) * 1000, 2 ) );	
		EnemyContainer.push_back( new Enemy3( (i+5) * 1000, 2 ) );	
		if (i%4==0)
			EnemyContainer.push_back( new Leader2( (i+5) * 1000, 3 ) );	
	}

	EnemyContainer.push_back( new Leader1( (35) * 1000, 4 ) );	

	for (i = 40; i<43; i++)
	{
		EnemyContainer.push_back( new Leader2( (i+5) * 1000 , 4) );	
		
		if (i%2==0)
			EnemyContainer.push_back( new Leader1( (i+5) * 1000 , 4) );			
	}

	for (i = 44; i<54; i++)
		EnemyContainer.push_back( new Enemy4( (i+5) * 1000 , 2) );		
	
	for (i = 55; i<75; i++)
	{
		if (i % 3 == 0 )
		{
			EnemyContainer.push_back( new Enemy1( (i+5) * 1000 , 2) );	
			EnemyContainer.push_back( new Enemy2( (i+5) * 1000 , 2) );	
			EnemyContainer.push_back( new Enemy3( (i+5) * 1000, 2 ) );	
//			EnemyContainer.push_back( new Leader2( (i+5) * 1000, 2 ) );	
		}

	}

	EnemyContainer.push_back( new BigBoss1( (90) * 1000 ,4 ) );	

		
}


