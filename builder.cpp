#include "builder.h"

builder::builder()
{
	EnemyContainer.clear();
}

void builder::buildstage1()
{
	for ( int i = 0; i < 50; i++ ) 
	{	
		EnemyContainer.push_back( new Enemy1( ( (2*i+5)+5 ) * 1000 ) );	
		EnemyContainer.push_back( new Enemy2( ( 2*i+5 ) * 1000 ) );	
	}
		
}

vector<BaseEnemy *> builder::getstage()
{
	return EnemyContainer;
}


