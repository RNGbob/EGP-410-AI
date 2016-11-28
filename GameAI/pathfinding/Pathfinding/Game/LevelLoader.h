#pragma once

#include "Game.h"
#include <vector>
#include "Grid.h"
#include "GridGraph.h"
#include "MapWallManager.h"
#include "ItemManager.h"
#include "GridVisualizer.h"

class Level : public Trackable
{
public:
	Level(Grid* pGrid);
	~Level();

	MapWallManager* getMapWalls() { return mpMapWalls; }
	ItemManager* getItemManager() { return mpItemManager; }
	Grid* getGrid() { return mpGrid; }
	GridGraph* getGridGraph() { return mpGridGraph; }
	
	void draw(GraphicsBuffer* pBuffer);

private:
	MapWallManager* mpMapWalls;
	ItemManager* mpItemManager;
	Grid* mpGrid;
	GridGraph* mpGridGraph;
	GridVisualizer* mpVisualizer;
	// EnemySpawner* mpSpawner;


};


class LevelLoader : public Trackable
{
public:
	LevelLoader();
	~LevelLoader() {} ;

	void init();
	void clear();

	std::string getFileName(int index) { return mFiles[index]; }
	Level* getLevel(int index);

private:
	std::vector<Level*> mLevels;
	std::string mFiles[4];
};


