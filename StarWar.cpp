#include "StarWar.h"
#include "CreateGame.h"

/*
CApplication* createCApplication() {

	PlayerFactory *f = new ConcretePlayerFactory1;
	
	return new StarWar(f);
} // The end of Method createCApplication
*/

//StarWar::StarWar(PlayerFactory* f) : CApplication() {
StarWar::StarWar(PlayerFactory *f) { 

		m_title = string( "Star War" );
		tempEnemy = NULL;
		bullet = NULL;

		lpDDMainMenu = NULL;
		lpDDBackGround = NULL;
		lpDDLevel = NULL;
		temptea = NULL;

		currentplayer = NULL;
		player1 = NULL;
		player2 = NULL;
		player3 = NULL;
		player4 = NULL;
		player5 = NULL;
		player6 = NULL;
		player7 = NULL;
		player8 = NULL;
		player9 = NULL;
		player10 = NULL;

		buildgamestage =NULL;

		gameState = 1;
		select = 333;
		iOption = 0;
		changeOption=0;
		pausetime = 0;

		stage = 1;
		gameclear = false;
		gameover = false;
		pressed = false;

		pFactory = f;

		buildgamestage = new ConcreteBuilder1;

		level = 1;

		SaveStage = 1;
		SaveHP = 600;
		SaveSpeed = 8;

//		GameOverW = new cSound("GameOver1.wav");

} // The end of Constructor

StarWar::~StarWar() {

	deleteGame();
//	delete Graphics();
//	delete Input();
//	delete Sound();
//	delete mainScreen();
		
	int i;
	i=0;
}

void StarWar::initGame() {

	gameover = false;

	for ( eviter i = enemyList.begin(); i!=enemyList.end(); i++ ) 	
		SafeDelete( *i );
	
	for ( bviter j = enemyBulletList.begin(); j!=enemyBulletList.end(); j++ ) 
		SafeDelete( *j );

	for ( vector<BaseTreasure *>::iterator k = treasureList.begin(); k!=treasureList.end(); k++ ) 
		SafeDelete( *k );

	enemyList.clear();
	enemyBulletList.clear();
	treasureList.clear();

	SafeRelease( lpDDMainMenu );
	SafeRelease( lpDDBackGround );
	SafeRelease( lpDDLevel );

	loadMainMenu();
	loadBackGround();
  	
	enemyList = buildgamestage->getstage(stage);
	
	player1 = pFactory->createplayer1();
	player2 = pFactory->createplayer2();
	player3 = pFactory->createplayer3();
	player4 = pFactory->createplayer4();
	player5 = pFactory->createplayer5();
	player6 = pFactory->createplayer6();
	player7 = pFactory->createplayer7();
	player8 = pFactory->createplayer8();
	player9 = pFactory->createplayer9();
	player10 = pFactory->createplayer10();
	
	pFactory->setTranform();
	
	currentplayer = player1;
	Input()->getKeyboard()->setReceiver( currentplayer );

	//tea = new Treasure;

} // The end of Method initGame

void StarWar::deleteGame() {

	SafeRelease( lpDDMainMenu );
	SafeRelease( lpDDBackGround );
	SafeRelease( lpDDLevel );
	
	SafeDelete( GameOverW );
	SafeDelete( pFactory );
	SafeDelete( buildgamestage );

	SafeDelete( currentplayer );
	SafeDelete( player1 );
	SafeDelete( player2 );
	SafeDelete( player3 );
	SafeDelete( player4 );
	SafeDelete( player5 );
	SafeDelete( player6 );
	SafeDelete( player7 );
	SafeDelete( player8 );
	SafeDelete( player9 );
	SafeDelete( player10 );
	
//	SafeDelete( tea );

	for ( eviter i = enemyList.begin(); i!=enemyList.end(); i++ ) 
		SafeDelete( *i );
	
	for ( bviter j = enemyBulletList.begin(); j!=enemyBulletList.end(); j++ ) 
		SafeDelete( *j );

	for ( tviter k = treasureList.begin(); k!= treasureList.end(); k++ ) 
		SafeDelete( *k );

	enemyList.clear();
	enemyBulletList.clear();
	treasureList.clear();

//	delete Graphics(); 
//	delete Input();
//	delete Sound();
//	delete mainScreen();

} // The end of Method deleteGame

void StarWar::DoFrame( float timeDelta ) {


	if( !Graphics() ) 
			throw GameError( "Graphics Factilities is not ready!!");

	if ( Input()->getKeyboard()->poll( DIK_ESCAPE ) ) {
	
		throw GameError(" The game is terminated by user !! ");
	
	}


	switch ( gameState ) {
	
		// gameState = 1, displaying the MainMenu of the game
		case 1:
			
			displayMainMenu();

			break;
		// gameState = 2, doing the game logic
		case 2:

			displayGame();

			if ( Input()->getKeyboard()->poll( DIK_P ) )			
				gameState = 6;

			if (Input()->getKeyboard()->poll( DIK_S ) )
				saveGame();
			
		//	View.displayGame();

			break;
		// gameState = 3, displaying the rasing level
		case 3:

			displayRaiseLevel();

			break;
		// gameState = 4, displaying the screen of game over
		case 4:

			displayGameOver();

			break;
		case 5:

			endGame();
			break;

		case 6:
			pauseGame();			
			break;

		default:
			throw GameError(" Error in the variable game state!!");
	
	}

	Graphics()->flip();

} // The end of Method DoFrame


void StarWar::loadMainMenu() {
	
	lpDDMainMenu = NULL;
	lpDDMainMenu = Graphics()->DDLoadBitmap( Graphics()->getDirectDraw(), 
											MAKEINTRESOURCE(IDB_MAINMENU), 
											0, 0 );

	if ( lpDDMainMenu == NULL )
		throw GameError(" Error in loadBitmap of MainMenu");

	lpDDCursor = NULL;
	lpDDCursor = Graphics()->DDLoadBitmap( Graphics()->getDirectDraw(),
											MAKEINTRESOURCE(IDB_Cursor), 
											0, 0 );
											
	if ( lpDDCursor == NULL )
		throw GameError(" Error in loadBitmap of Cursor");

	HRESULT ddrval = Graphics()->DDSetColorKey( lpDDCursor, CLR_INVALID );
	if ( ddrval!= DD_OK )
		throw GameError("Error in DDSetColorKey" );




} // The end of Method loadMainMenu

void StarWar::loadBackGround() {

	lpDDBackGround = NULL;
	lpDDBackGround = Graphics()->DDLoadBitmap( Graphics()->getDirectDraw(), 
										MAKEINTRESOURCE(IDB_BACKGROUND), 
										0, 0 );

	if ( lpDDBackGround == NULL )
		throw GameError(" Error in loadBitmap of BackGround");
		
} // The end of Method loadBackGround

void StarWar::displayMainMenu() {

	HRESULT ddrval;

	ddrval = Graphics()->getBackBuffer()->BltFast( 0, 0, lpDDMainMenu, NULL, FALSE  );
	ddrval = Graphics()->getBackBuffer()->BltFast( 210, select, lpDDCursor, NULL, TRUE);

//	if ( ddrval != DD_OK ) 
//		throw GameError( "Error in displayMainMenu function ");
	
	if ( Input()->getKeyboard()->poll( DIK_RETURN ) ) 
	{
		HRESULT ddrval = Graphics()->getBackBuffer()->BltFast( 0, 0, lpDDBackGround, NULL, FALSE );
		currentplayer->setXY(70,200);
		currentplayer->setstate(0);

		gameState = 2;

		if (select == 370)
			loadGame();

		timer.Start();
	}

	
	if ( ( Input()->getKeyboard()->poll( DIK_UP ) || Input()->getKeyboard()->poll( DIK_DOWN ) ) && (!pressed))
	{
//		pressed = true;
		iOption++;
		changeOption++;

		if (changeOption >8)
		{
			if (iOption%2 == 0)
				select = 333;
			else
				select = 370;													
		}
	}
	
	if (changeOption > 8)
 		changeOption=0;

} // The end of Method displayMainMenu

void StarWar::displayBackGround() {

	HRESULT ddrval;

	RECT		rcRect;


	static		x = 0 ;
	const int	iFim = 640;

	x += currentplayer->getSpeed()*1.5;

	if (x > iFim)
		x=0;

	rcRect.left = 0;
    rcRect.top = 0;
    rcRect.right = 640-(iFim - x);
    rcRect.bottom = 480;


	while (1)
	{
		ddrval = Graphics()->getBackBuffer()->BltFast( iFim-x, 0, lpDDBackGround, &rcRect, FALSE );

		if ( ddrval == DD_OK )
		{
			break;
		}
		if ( ddrval == DDERR_SURFACELOST )
		{

		}
		if ( ddrval != DDERR_WASSTILLDRAWING )
			break;
	}

	rcRect.left = 640-(iFim-x);
	rcRect.top = 0;
	rcRect.right = iFim;
    rcRect.bottom = 480;

	while (1)
	{
		ddrval = Graphics()->getBackBuffer()->BltFast( 0, 0, lpDDBackGround, &rcRect, FALSE );

		if ( ddrval == DD_OK )
			{
				break;
			}
			if ( ddrval == DDERR_SURFACELOST )
			{
	//		hRet = RestoreSurfaces();
	//			if (hRet != DD_OK)
	//				break;
			}
			if ( ddrval != DDERR_WASSTILLDRAWING )
				break;

	}
//	if ( ddrval != DD_OK )
//		throw GameError( "Error in displayBackGround function ");
       


} // The end of Method displayBackGround

void StarWar::displayGame() {

	displayBackGround();

	char temp[20];
	sprintf(temp ,"%d",stage);	
	currentplayer->getScorePt()->bltText("STAGE",280,400);
	currentplayer->getScorePt()->bltText(temp,370,400);


	if ( currentplayer->changeNextMode() )
	{
		currentplayer = currentplayer->getNextMode();
		Input()->getKeyboard()->setReceiver( currentplayer );
	}

	CheckGameClear();

	ShowEnemyList();
	ShowEnemyBulletList();
	ShowTreasureBulletList();

	currentplayer->draw( Graphics()->getBackBuffer() ,  enemyBulletList, enemyList, treasureList);

	CheckGameOverWin();

} // The end of Method displayGame

void StarWar::displayRaiseLevel() {

	for (vector<BaseEnemy *>::iterator it =enemyList.begin(); it != enemyList.end(); it++)
			SafeDelete(*it);
	
	for (vector<BaseBullet *>::iterator it2 =enemyBulletList.begin(); it2 != enemyBulletList.end(); it2++)
		SafeDelete(*it2);

	for (vector<BaseTreasure *>::iterator it3 =treasureList.begin(); it3 != treasureList.end(); it3++)
		SafeDelete(*it3);

	enemyList.clear();
	enemyBulletList.clear();
	treasureList.clear();

	currentplayer->setStrength(600);
	currentplayer->setXY(70,200);
	currentplayer->setstate(0);

	stage++;

	enemyList = buildgamestage->getstage(stage);

	gameclear = false;
	gameState = 2;
	timer.Start();
	
	if (enemyList.size() ==0 )
		gameover = true;
	

} // The end of Method displayRaiseLevel

void StarWar::displayGameOver() {
	
//	if ( !GameOverW->IsPlaying() )
//		GameOverW->Play();

	displayBackGround();
	currentplayer->getScorePt()->bltText("GAMEOVER",250,200);
	
	stage = 1;	// re-initialize the game

	if ( destroytimer.Elapsed() > 3000 )
	{
		gameState =1;	// load menu
		initGame();
	}

} // The end of Method displayGameOver

void StarWar::endGame()
{
	displayBackGround();
	currentplayer->getScorePt()->bltText("YOU WIN",250,200);
	currentplayer->setXY(280,300);
	currentplayer->draw( Graphics()->getBackBuffer() ,  enemyBulletList, enemyList, treasureList);

	if ( Input()->getKeyboard()->poll( DIK_X ) )
	{
		stage = 1;
		gameState = 1;
		gameover = false;
		gameclear = false;		

		delete buildgamestage;
		buildgamestage = new ConcreteBuilder2;

		initGame();
	}

}

void StarWar::ShowEnemyList()
{
	// Check whether the enemyList contains enmey 
	if ( enemyList.size() != 0 ) 
		// Loop for draw and perform the action of enemy
		for ( eviter i = enemyList.begin(); i!=enemyList.end(); i++ ) 
			// Check whether the enemy is valid first
			if ( *i != NULL ) 
				if ( (*i)->getTimeAppear() < timer.Elapsed() - pausetime ||(*i)->getappear())
				{
					(*i)->setappear();
					if ( (*i)->getState() != 1 )	// if not destroyed
						(*i)->CheckHit( currentplayer->getBulletList() ); 	// check hit by player bullet
				
					if ( !(*i)->isDestroyMe()  ) 
					{	
						(*i)->draw( Graphics()->getBackBuffer() );	
						(*i)->getStrategy()->TrackPlayerPosition(currentplayer);
						(*i)->getStrategy()->ApproachPlayer(*i);
						enemyBulletList.push_back( (*i)->getStrategy()->TimetoAttack( *i ) );						
					}
					else
					{
						if ( (*i)->getState() == 1 )
						{
							currentplayer->getScorePt()->addscore( (*i)->getpoint() );	// add score

							temptea = (*i)->createTreasure(rand()%5);
							if (temptea != NULL)
							{
								temptea->setXY( (*i)->getXPos(), (*i)->getYPos()+20 );
								treasureList.push_back(temptea);					
							}
						}

						SafeDelete(*i);
					}

				}
}

void StarWar::ShowEnemyBulletList()
{
	// Check whether the enemyBulletList contain bullet first
	if ( enemyBulletList.size() != 0 ) 	
		// Loop for draw and perform the action of enemy
		for ( bviter i = enemyBulletList.begin(); i!=enemyBulletList.end(); i++ ) 
			// Check whether the enemy is valid first
			if ( *i != NULL ) 
			{
				if ( (*i)->getDestroy() == 1) 
					SafeDelete(*i);
				else
					(*i)->draw( Graphics()->getBackBuffer(), currentplayer->getXPos(), currentplayer->getYPos() );	
			}
}

void StarWar::ShowTreasureBulletList()
{
	if ( treasureList.size() != 0)	
		for ( vector<BaseTreasure *>::iterator i = treasureList.begin(); i!=treasureList.end(); i++ ) 
			if (*i != NULL)
			{
				if ( (*i)->getDestroy() == 1) 
					SafeDelete(*i);
				else
					(*i)->draw( Graphics()->getBackBuffer() );
			}
}

void StarWar::CheckGameClear()
{
	int count=0;	

	for (int i=0; i<enemyList.size(); i++)
	{
		eviter it = enemyList.begin()+i;

		if ( (*it) == NULL)
			count++;				
	}

	if ((count == enemyList.size()) && (!gameclear))
	{
		gameclear = true;
		destroytimer.Start();					
	}
	
	if (gameclear)
		currentplayer->getScorePt()->bltText("GAME CLEAR",250,200);

	if (gameclear && destroytimer.Elapsed() > 2500)
	{			
		gameState =3;
	}
}

void StarWar::CheckGameOverWin()
{
	if ( currentplayer->isDestroyMe() && !gameover)
	{
		gameclear = false;
		gameover = true;
		destroytimer.Start();
	}
	
	if (gameover)
	{
	//	currentplayer->getScorePt()->bltText("GAMEOVER",250,200);

	//	if (destroytimer.Elapsed() > 1500)
			gameState = 4;
	}

	if (gameover && !currentplayer->isDestroyMe())
		gameState =5;
}

void StarWar::pauseGame()
{
	static cnt = 0;
	static ES_FlashTimer pauseTimer;


	if (cnt ==0)	
		pauseTimer.Start();


	cnt++;

	displayBackGround();

	if (cnt > 30)
	{		
		currentplayer->getScorePt()->bltText("PAUSE",280,200);	
		currentplayer->getScorePt()->bltText("PRESS R TO RESUME",200,240);	
		
		if (cnt > 60)
			cnt = 1;
	}

	if ( Input()->getKeyboard()->poll( DIK_R ) )
	{
		pausetime += pauseTimer.Elapsed();
		cnt = 0;
		gameState = 2;
	}
}

void StarWar::saveGame()
{
	currentplayer->getScorePt()->bltText(" SAVE",280,240);	
	
	SaveStage = stage;
	SaveHP = currentplayer->getStrength();
	SaveSpeed = currentplayer->getSpeed();

	SaveEnemyBulletList = enemyBulletList;
	SaveEnemyList = enemyList;
	SaveTreasureList = treasureList;
}

void StarWar::loadGame()
{
	stage = SaveStage;

	for ( eviter i = enemyList.begin(); i!=enemyList.end(); i++ ) 
		SafeDelete( *i );
	
	enemyList.clear();

	enemyList = buildgamestage->getstage(stage);

	/*
	SafeDelete(currentplayer);

	if (SaveSpeed == 8)
		currentplayer = new PlayerPlaneMode1;
	else
		currentplayer = new PlayerPlaneMode2;
	
	currentplayer->setStrength( SaveHP );
	enemyBulletList = SaveEnemyBulletList;
	enemyList = SaveEnemyList;
	treasureList = SaveTreasureList;
	*/
}