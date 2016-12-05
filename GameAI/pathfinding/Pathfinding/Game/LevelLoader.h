#pragma once

#include "Game.h"
#include <vector>
#include "Grid.h"
#include "GridGraph.h"
#include "MapWallManager.h"
#include "ItemManager.h"
#include "GridVisualizer.h"
#include "Astar.h"

class Level : public Trackable
{
public:
	Level(Grid* pGrid);
	~Level();

	MapWallManager* getMapWalls() const { return mpMapWalls; }
	ItemManager* getItemManager() const { return mpItemManager; }
	Grid* getGrid() const { return mpGrid; }
	GridGraph* getGridGraph() const { return mpGridGraph; }
	void setIndex(int i) { mIndex = i; }

	void draw(GraphicsBuffer* pBuffer);

	const Path& findPath(Vector2D from, Vector2D to);
	int getExitIndex(int cLevel);

protected:
	MapWallManager* mpMapWalls;
	ItemManager* mpItemManager;
	Grid* mpGrid;
	GridGraph* mpGridGraph;
	GridVisualizer* mpVisualizer;
	GridPathfinder* mpPathfinder;
	int mIndex;


};


class LevelLoader : public Trackable
{
public:
	LevelLoader();
	~LevelLoader() ;

	void init();
	void clear();

	std::string getFileName(int index) { return mFiles[index]; }
	Level* getLevel(int index);

private:
	std::vector<Level*> mLevels;
	std::string mFiles[4];
};


