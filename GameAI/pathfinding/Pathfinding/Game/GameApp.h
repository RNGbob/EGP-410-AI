#pragma once

/*Game - class to hold all game related info.

Dean Lawson
Champlain College
2011
*/

#include "Game.h"

//forward declarations
class GraphicsBuffer;
class Sprite;
class KinematicUnit;
class GameMessageManager;
class Grid;
class GridVisualizer;
class GridGraph;
class GridPathfinder;
class DebugDisplay;
class InputSystem;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

const IDType BACKGROUND_ID = 0;
const IDType PLAYER_SPRITE_ID = 1;
const IDType ENEMY_PURPLE_SPRITE_ID = 2;
const IDType ENEMY_GREEN_SPRITE_ID = 3;
const IDType ENEMY_ORANGE_SPRITE_ID = 4;
const IDType ENEMY_LIME_SPRITE_ID = 5;

const int GRID_SQUARE_SIZE = 32;
const std::string gFileName = "pathgrid.txt";

enum PathfindingType
{
	DepthBreadthSearch = 0,
	DijkstraPath,
	AstarPath

};


class GameApp: public Game
{
public:
	GameApp();
	~GameApp();

	virtual bool init();
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual void draw();
	virtual void update();
	virtual void input();
	virtual bool endLoop();

	//accessors
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline GridVisualizer* getGridVisualizer() { return mpGridVisualizer; };
	inline GridPathfinder* getPathfinder() { return mpPathfinder; };
	inline Grid* getGrid() { return mpGrid; };
	inline GridGraph* getGridGraph() { return mpGridGraph; };

	void setPathFinding(GridPathfinder* newPF);

	void setDepthBreadth();
	void setDijkstra();
	void setAstar();

	PathfindingType getType() { return mCurrentType; }

private:
	GameMessageManager* mpMessageManager;
	Grid* mpGrid;
	GridVisualizer* mpGridVisualizer;
	GridGraph* mpGridGraph;
	DebugDisplay* mpDebugDisplay;

	InputSystem* mpInput;

	GridPathfinder* mpPathfinder;

	//GridPathfinder* mpDepthBreadth;
	//GridPathfinder* mpDijkstra;
	//GridPathfinder* mpAstar;

	PathfindingType mCurrentType;

};

