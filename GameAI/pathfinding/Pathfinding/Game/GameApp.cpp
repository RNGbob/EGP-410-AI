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

#include <fstream>
#include <vector>

const IDType BACKGROUND_ID = ENDING_SEQUENTIAL_ID + 1;
const int GRID_SQUARE_SIZE = 32;
const std::string gFileName = "pathgrid.txt";

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

	//create the GridGraph for pathfinding
	mpGridGraph = new GridGraph(mpGrid);
	//init the nodes and connections
	mpGridGraph->init();

	mCurrentType = DepthBreadthSearch;

	mpPathfinder = new DepthFirstPathfinder(mpGridGraph);

	//load buffers
	mpGraphicsBufferManager->loadBuffer( BACKGROUND_ID, FILE_PATH+"wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( BACKGROUND_ID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
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

}

void GameApp::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void GameApp::processLoop()
{
	
	draw();
	
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

}

void GameApp::update()
{
	
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
