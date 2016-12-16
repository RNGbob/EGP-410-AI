#include <allegro5/allegro.h>
#include "Game.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Vector2D.h"
#include "Grid.h"
#include "GridGraph.h"
#include "Connection.h"
#include "Path.h"
#include "DepthFirstPathfinder.h"
#include "Pathfinder.h"
#include "GridPathfinder.h"
#include "GridVisualizer.h"
#include "DebugDisplay.h"
#include "PathfindingDebugContent.h"

#include "InputSystem.h"
#include "Astar.h"
#include "Dijkstra.h"

#include "UnitManager.h"
#include "MapWallManager.h"
#include "ItemManager.h"
#include "LevelLoader.h"
#include "Player.h"
#include "Enemy.h"

#include <fstream>
#include <vector>




//const int WIDTH = 1024;
//const int HEIGHT = 768;


GameApp::GameApp()
:mpMessageManager(NULL)
,mpGrid(NULL)
,mpGridGraph(NULL)
,mpPathfinder(NULL)
,mpDebugDisplay(NULL)
,mCurrentLevelIndex(0)
,mNumEnemies(1)
{
	
}

GameApp::~GameApp()
{
	cleanup();
}

bool GameApp::init()
{
	bool retVal = Game::init();
	if( retVal == false )
	{

		return false;
	}

	mpMessageManager = new GameMessageManager();

	mpInput = new InputSystem();
	mpInput->init(mpMessageManager);

	initAssets();

	//create and load the Grid, GridBuffer, and GridRenderer
	/*
	mpGrid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	mpGridVisualizer = new GridVisualizer( mpGrid );
	std::ifstream theStream( gFileName );
	mpGrid->load( theStream );
	
	
	mpMapWalls = new MapWallManager();
	mpMapWalls->initWalls(mpGrid);
	
	mpItemManager = new ItemManager();

	mpGridGraph = new GridGraph(mpGrid);
	//init the nodes and connections
	mpGridGraph->init();
	*/
	
	mpLevelLoader = new LevelLoader();
	mpLevelLoader->init();
	mpCurrentLevel = mpLevelLoader->getLevel(0);
	
	
	mpUnits = new UnitManager();
	mpPlayer = new Player(mpSpriteManager->getSprite(PLAYER_SPRITE_ID), mpCurrentLevel->getPlayerSpawn(), 0, Vector2D(0, 0), 0.0f, 200.0f, 10.0f);
	mpUnits->init(mpSpriteManager);

	
	//create the GridGraph for pathfinding
	//Enemy*  = dynamic_cast<Enemy*>(mpUnits->getUnit(0));
	mpUnits->getUnit(0)->getEnemyptr()->init();
	mCurrentType = DepthBreadthSearch;

	//mpPathfinder = new DepthFirstPathfinder(mpGridGraph);

	//debug display
	PathfindingDebugContent* pContent = new PathfindingDebugContent( mpPathfinder );
	mpDebugDisplay = new DebugDisplay( Vector2D(0,12), pContent );

	mpMasterTimer->start();
	mtimer = gpGame->getCurrentTime();
	return true;
}

void GameApp::initAssets()
{
	//load buffers
	mpGraphicsBufferManager->loadBuffer(BACKGROUND_ID, FILE_PATH + "wallpaper.bmp");
	mpGraphicsBufferManager->loadBuffer(PLAYER_SPRITE_ID, FILE_PATH + "Player.png");
	mpGraphicsBufferManager->loadBuffer(ENEMY_PURPLE_SPRITE_ID, FILE_PATH + "EnemyPurple.png");
	mpGraphicsBufferManager->loadBuffer(ENEMY_GREEN_SPRITE_ID, FILE_PATH + "EnemyGreen.png");
	mpGraphicsBufferManager->loadBuffer(ENEMY_ORANGE_SPRITE_ID, FILE_PATH + "EnemyOrange.png");
	mpGraphicsBufferManager->loadBuffer(ENEMY_LIME_SPRITE_ID, FILE_PATH + "EnemyLime.png");
	mpGraphicsBufferManager->loadBuffer(ENEMY_WEAK_SPRITE_ID, FILE_PATH + "EnemyWeak.png");
	mpGraphicsBufferManager->loadBuffer(COIN_SPRITE_ID, FILE_PATH + "Coin.png");
	mpGraphicsBufferManager->loadBuffer(CANDY_SPRITE_ID, FILE_PATH + "Candy.png");


	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer(BACKGROUND_ID);
	if (pBackGroundBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight());
	}
	GraphicsBuffer* pPlayerBuffer = mpGraphicsBufferManager->getBuffer(PLAYER_SPRITE_ID);
	if (pPlayerBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(PLAYER_SPRITE_ID, pPlayerBuffer, 0, 0, pPlayerBuffer->getWidth(), pPlayerBuffer->getHeight());
	}
	GraphicsBuffer* pEnemy1Buffer = mpGraphicsBufferManager->getBuffer(ENEMY_PURPLE_SPRITE_ID);
	if (pEnemy1Buffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(ENEMY_PURPLE_SPRITE_ID, pEnemy1Buffer, 0, 0, pEnemy1Buffer->getWidth(), pEnemy1Buffer->getHeight());
	}
	GraphicsBuffer* pEnemy2Buffer = mpGraphicsBufferManager->getBuffer(ENEMY_GREEN_SPRITE_ID);
	if (pEnemy2Buffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(ENEMY_GREEN_SPRITE_ID, pEnemy2Buffer, 0, 0, pEnemy2Buffer->getWidth(), pEnemy2Buffer->getHeight());
	}
	GraphicsBuffer* pEnemy3Buffer = mpGraphicsBufferManager->getBuffer(ENEMY_ORANGE_SPRITE_ID);
	if (pEnemy3Buffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(ENEMY_ORANGE_SPRITE_ID, pEnemy3Buffer, 0, 0, pEnemy3Buffer->getWidth(), pEnemy3Buffer->getHeight());
	}
	GraphicsBuffer* pEnemy4Buffer = mpGraphicsBufferManager->getBuffer(ENEMY_LIME_SPRITE_ID);
	if (pEnemy4Buffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(ENEMY_LIME_SPRITE_ID, pEnemy4Buffer, 0, 0, pEnemy4Buffer->getWidth(), pEnemy4Buffer->getHeight());
	}
	GraphicsBuffer* pEnemyWeakBuffer = mpGraphicsBufferManager->getBuffer(ENEMY_WEAK_SPRITE_ID);
	if (pEnemyWeakBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(ENEMY_WEAK_SPRITE_ID, pEnemyWeakBuffer, 0, 0, pEnemyWeakBuffer->getWidth(), pEnemyWeakBuffer->getHeight());
	}
	GraphicsBuffer* pCoinBuffer = mpGraphicsBufferManager->getBuffer(COIN_SPRITE_ID);
	if (pCoinBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(COIN_SPRITE_ID, pCoinBuffer, 0, 0, pCoinBuffer->getWidth(), pCoinBuffer->getHeight());
	}
	GraphicsBuffer* pCandyBuffer = mpGraphicsBufferManager->getBuffer(CANDY_SPRITE_ID);
	if (pCandyBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(CANDY_SPRITE_ID, pCandyBuffer, 0, 0, pCandyBuffer->getWidth(), pCandyBuffer->getHeight());
	}
}

void GameApp::cleanup()
{
	delete mpMessageManager;
	mpMessageManager = NULL;

	/*
	delete mpGrid;
	mpGrid = NULL;

	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpGridGraph;
	mpGridGraph = NULL;
*/
	delete mpPathfinder;
	mpPathfinder = NULL;

	delete mpDebugDisplay;
	mpDebugDisplay = NULL;

	delete mpInput;
	mpInput = NULL;

	delete mpUnits;
	mpUnits = NULL;
	
	delete mpPlayer;
	mpPlayer = NULL;
	/*
	delete mpMapWalls;
	mpMapWalls = NULL;

	delete mpItemManager;
	mpItemManager = NULL;
*/
	//delete mpCurrentLevel;
	//mpCurrentLevel = NULL;

	delete mpLevelLoader;
	mpLevelLoader = NULL;

}

void GameApp::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void GameApp::processLoop()
{
	draw();
	update();
	input();
	//std::cout << "do this to me" << std::endl;
	mpMessageManager->processMessagesForThisframe();
	
	//should be last thing in processLoop
	Game::processLoop();
}

void GameApp::draw()
{
	//get back buffer
	GraphicsBuffer* pBackBuffer = mpGraphicsSystem->getBackBuffer();
	//copy to back buffer
	//mpGridVisualizer->draw(*pBackBuffer);
#ifdef VISUALIZE_PATH
	//show pathfinder visualizer
	//mpPathfinder->drawVisualization(mpGrid, pBackBuffer);
#endif
	
	mpCurrentLevel->draw(pBackBuffer);
	mpPlayer->draw(pBackBuffer);
	mpUnits->draw(pBackBuffer);
	mpDebugDisplay->draw( pBackBuffer );
}

void GameApp::update()
{
	mpUnits->update(LOOP_TARGET_TIME/1000.0f);
	mpPlayer->update(LOOP_TARGET_TIME / 1000.0f);
	if (((gpGame->getCurrentTime() -mtimer)) >=  10000 && mNumEnemies < 12 )
	{
		mtimer = gpGame->getCurrentTime();
		mpUnits->getUnit(mNumEnemies)->getEnemyptr()->init();
		mNumEnemies++;
	}


}

void GameApp::input()
{
	mpInput->update();

}

bool GameApp::endLoop()
{
	mpLoopTimer->sleepUntilElapsed(LOOP_TARGET_TIME);
	return Game::endLoop();
}

Player* GameApp::getPlayerUnit()
{
	return mpPlayer; 
}

UnitManager * GameApp::getUnitManager()
{
	return mpUnits;
}

ItemManager * GameApp::getItemManager()
{
	//return mpItemManager;
	return mpCurrentLevel->getItemManager();
}

LevelLoader * GameApp::getLevelLoader()
{
	return mpLevelLoader;
}

Level * GameApp::getLevel()
{
	return mpCurrentLevel;
}

Level * GameApp::switchLevel(int index)
{
	// move everything based off direction moving
	Vector2D delta;
	if ((mCurrentLevelIndex == 0 && index == 1) || (mCurrentLevelIndex == 2 && index == 3))
	{
		delta = Vector2D(-WIDTH,0);// right 
	}
	else if ((mCurrentLevelIndex == 1 && index == 0) || (mCurrentLevelIndex == 3 && index == 2))
	{
		delta = Vector2D(WIDTH,0 );//left
	}
	else if ((mCurrentLevelIndex == 0 && index == 2) || (mCurrentLevelIndex == 1 && index == 3))
	{
		delta = Vector2D(0, -HEIGHT);// bottom 
	}
	else if ((mCurrentLevelIndex == 2 && index == 0) || (mCurrentLevelIndex == 3 && index == 1))
	{
		delta = Vector2D(0, HEIGHT); //top
	}

	//mpUnits->getUnit(0)->modPosistion(delta); // first enemy test, switch to all active enemies
	mpUnits->moveEnemies(delta);
	mCurrentLevelIndex = index;
	mpCurrentLevel = mpLevelLoader->getLevel(index);
	
	return mpCurrentLevel;
}

void GameApp::setPathFinding(GridPathfinder * newPF)
{
	mpPathfinder->clearPath();
	delete mpPathfinder;
	delete mpDebugDisplay;
	mpPathfinder = newPF;
	PathfindingDebugContent* pContent = new PathfindingDebugContent(mpPathfinder);
	mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), pContent);


}

void GameApp::restart()
{
	for (int i = 0; i < mNumEnemies; i++)
	{
		mpUnits->getUnit(i)->getEnemyptr()->reset();
	}
	
	mpLevelLoader->reload();
	mpPlayer->reset();
	mpUnits->getUnit(0)->getEnemyptr()->init();
	mNumEnemies = 1;
	



}

void GameApp::setDepthBreadth()
{
	DepthFirstPathfinder* pDFpathfinder = new DepthFirstPathfinder(mpGridGraph);
	setPathFinding(pDFpathfinder);
	mCurrentType = DepthBreadthSearch;
}

void GameApp::setDijkstra()
{
	Dijkstra* pDijkstra = new Dijkstra(mpGridGraph);
	setPathFinding(pDijkstra);
	mCurrentType = DijkstraPath;
}

void GameApp::setAstar()
{
	Astar* pAstar = new Astar(mpGridGraph);
	setPathFinding(pAstar);
	mCurrentType = AstarPath;
}
