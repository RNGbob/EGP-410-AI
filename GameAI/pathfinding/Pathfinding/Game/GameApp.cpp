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

	//create and load the Grid, GridBuffer, and GridRenderer
	mpGrid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	mpGridVisualizer = new GridVisualizer( mpGrid );
	std::ifstream theStream( gFileName );
	mpGrid->load( theStream );

	mpUnits = new UnitManager();
	mpUnits->init(mpSpriteManager);

	mpMapWalls = new MapWallManager();
	mpMapWalls->initWalls(mpGrid);

	//create the GridGraph for pathfinding
	mpGridGraph = new GridGraph(mpGrid);
	//init the nodes and connections
	mpGridGraph->init();

	mCurrentType = DepthBreadthSearch;

	mpPathfinder = new DepthFirstPathfinder(mpGridGraph);

	//load buffers
	mpGraphicsBufferManager->loadBuffer( BACKGROUND_ID, FILE_PATH+"wallpaper.bmp");
	mpGraphicsBufferManager->loadBuffer(PLAYER_SPRITE_ID, FILE_PATH + "Player.bmp");
	mpGraphicsBufferManager->loadBuffer(ENEMY_PURPLE_SPRITE_ID, FILE_PATH + "EnemyPurple.bmp");
	mpGraphicsBufferManager->loadBuffer(ENEMY_GREEN_SPRITE_ID, FILE_PATH + "EnemyGreen.bmp");
	mpGraphicsBufferManager->loadBuffer(ENEMY_ORANGE_SPRITE_ID, FILE_PATH + "EnemyOrange.bmp");
	mpGraphicsBufferManager->loadBuffer(ENEMY_LIME_SPRITE_ID, FILE_PATH + "EnemyLime.bmp");
	

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( BACKGROUND_ID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
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
		mpSpriteManager->createAndManageSprite(ENEMY_PURPLE_SPRITE_ID, pEnemy2Buffer, 0, 0, pEnemy2Buffer->getWidth(), pEnemy2Buffer->getHeight());
	}
	GraphicsBuffer* pEnemy3Buffer = mpGraphicsBufferManager->getBuffer(ENEMY_ORANGE_SPRITE_ID);
	if (pEnemy3Buffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(ENEMY_PURPLE_SPRITE_ID, pEnemy3Buffer, 0, 0, pEnemy3Buffer->getWidth(), pEnemy3Buffer->getHeight());
	}
	GraphicsBuffer* pEnemy4Buffer = mpGraphicsBufferManager->getBuffer(ENEMY_LIME_SPRITE_ID);
	if (pEnemy4Buffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(ENEMY_PURPLE_SPRITE_ID, pEnemy4Buffer, 0, 0, pEnemy4Buffer->getWidth(), pEnemy4Buffer->getHeight());
	}


	//debug display
	PathfindingDebugContent* pContent = new PathfindingDebugContent( mpPathfinder );
	mpDebugDisplay = new DebugDisplay( Vector2D(0,12), pContent );

	mpMasterTimer->start();
	return true;
}

void GameApp::cleanup()
{
	delete mpMessageManager;
	mpMessageManager = NULL;

	delete mpGrid;
	mpGrid = NULL;

	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpGridGraph;
	mpGridGraph = NULL;

	delete mpPathfinder;
	mpPathfinder = NULL;

	delete mpDebugDisplay;
	mpDebugDisplay = NULL;

	delete mpInput;
	mpInput = NULL;

	delete mpUnits;
	mpUnits = NULL;

	delete mpMapWalls;
	mpMapWalls = NULL;

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
	
	mpMessageManager->processMessagesForThisframe();
	
	//should be last thing in processLoop
	Game::processLoop();
}

void GameApp::draw()
{
	//get back buffer
	GraphicsBuffer* pBackBuffer = mpGraphicsSystem->getBackBuffer();
	//copy to back buffer
	mpGridVisualizer->draw(*pBackBuffer);
#ifdef VISUALIZE_PATH
	//show pathfinder visualizer
	mpPathfinder->drawVisualization(mpGrid, pBackBuffer);
#endif
	mpDebugDisplay->draw( pBackBuffer );

	//mpUnits->draw(pBackBuffer);

}

void GameApp::update()
{
	//mpUnits->update(LOOP_TARGET_TIME/1000.0f);
}

void GameApp::input()
{
	mpInput->update();

}

bool GameApp::endLoop()
{
	return Game::endLoop();
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
