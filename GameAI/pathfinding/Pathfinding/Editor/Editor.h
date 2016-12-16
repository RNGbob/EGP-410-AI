#pragma once

#include "Game.h"
#include "GraphicsSystem.h"
#include <fstream>
#include <vector>

/*Editor - class to hold all application related info.

Dean Lawson
Champlain College
2011
*/

//forward declarations
class GraphicsBuffer;
class Sprite;
class Grid;
class GridVisualizer;
class GraphicsBuffer;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame
const std::string FILE_NAME = FILE_PATH + "Level";// "pathgrid.txt";


class Editor: public Game
{
public:
	Editor();
	virtual ~Editor();

	inline Grid* getGrid() { return mpGrid; };
	inline GridVisualizer* getGridVisualizer() { return mpGridVisualizer; };

	virtual bool init();
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	void saveGrid( std::ofstream& theStream );
	void loadGrid( std::ifstream& theStream );
	void clearGrid();

	void setPlayerSpawn();
	void setEnemySpawn();
	void draw();
	bool shift(ALLEGRO_KEYBOARD_STATE keyState);
	bool firstPress(ALLEGRO_MOUSE_STATE& now, ALLEGRO_MOUSE_STATE& last, int mouseButton);

private:
	Grid* mpGrid;
	GridVisualizer* mpGridVisualizer;
	ALLEGRO_MOUSE_STATE prevKey;
	char mLevelIndex;
	int PlayerIndex;
	int EnemyIndex;

};