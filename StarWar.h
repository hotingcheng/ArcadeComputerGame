#ifndef STARWAR_H
#define STARWAR_H

#include <time.h>
#include "CApplication.h"

#include "BaseEnemy.h"

#include "builder.h"
#include "ConcreteBuilder1.h"
#include "ConcreteBuilder2.h"

#include "PlayerFactory.h"
#include "ConcretePlayerFactory1.h"

#include "BasePlayerPlane.h"
#include "BaseTreasure.h"

#include "BaseTreasure.h"

#include "es_TIMER.h"
#include <string>
using namespace std;

typedef vector< BaseEnemy* >::iterator eviter;
typedef vector< BaseBullet* >::iterator bviter;
typedef vector< BaseTreasure* >::iterator tviter;

class StarWar : public CApplication {

public:

	StarWar(PlayerFactory*);	// Constructor 
	~StarWar();	// Destructor

	virtual void DoFrame( float );

	inline virtual void initGame();
	inline virtual void deleteGame();

protected:

	// Load the MainMenu bitmap to the surface
	inline void loadMainMenu();

	// Load the BackGround bitmap to the surface
	inline void loadBackGround();


	// This protected method is called to display the Main Menu
	inline void displayMainMenu();

	// This protected method is called to diaplay the Game BackGround
	inline void displayBackGround();

	// This protected method is called to display the Game Content and perform game logic
	inline void displayGame();

	// This protected method is called to display the screen of rasing level
	inline void displayRaiseLevel();

	// This protected method is called to display the screen of game over
	inline void displayGameOver();

	// This protected method is called to display the screen of end of the game 
	inline void endGame();

	// This protected method is called to display the screen of end of the game 
	inline void pauseGame();

	inline void saveGame();
	inline void loadGame();

	// 1 - MainMenu
	// 2 - Game Logic
	// 3 - rasing level
	// 4 - game over
	// 5 - you win
	int gameState;


	// The level of the current
	int level;
	int select;
	int iOption;
	int changeOption;
	
	LPDIRECTDRAWSURFACE7 lpDDCursor;
	LPDIRECTDRAWSURFACE7 lpDDMainMenu;
	LPDIRECTDRAWSURFACE7 lpDDBackGround;
	LPDIRECTDRAWSURFACE7 lpDDLevel;

	ES_FlashTimer timer;
	ES_FlashTimer destroytimer;

	bool gameover;

	int lastTickCount;

	
	BaseEnemy* tempEnemy;
	vector< BaseEnemy* > enemyList;
	vector< BaseTreasure* > treasureList;
	vector< BaseBullet* > enemyBulletList;

	int SaveHP;
	int SaveStage;
	int SaveSpeed;
	vector< BaseEnemy* > SaveEnemyList;
	vector< BaseTreasure* > SaveTreasureList;
	vector< BaseBullet* > SaveEnemyBulletList;

	BaseBullet* bullet;

	BasePlayerPlane* currentplayer;

	BasePlayerPlane* player1;
	BasePlayerPlane* player2;
	BasePlayerPlane* player3;
	BasePlayerPlane* player4;
	BasePlayerPlane* player5;
	BasePlayerPlane* player6;
	BasePlayerPlane* player7;
	BasePlayerPlane* player8;
	BasePlayerPlane* player9;
	BasePlayerPlane* player10;

	BaseTreasure* temptea;

	PlayerFactory *pFactory;

	int stage;
	long pausetime;

	builder *buildgamestage;

	bool pressed;
	bool gameclear;

	inline void CheckGameOverWin();
	inline void CheckGameClear();
	inline void ShowEnemyList();
	inline void ShowEnemyBulletList();
	inline void ShowTreasureBulletList();

	cSound *GameOverW;
};

#endif