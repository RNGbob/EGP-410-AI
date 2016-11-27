#pragma once

#include "Game.h"
#include <vector>
#include "Grid.h"
#include "MapWallManager.h"
#include "ItemManager.h"

class Level : public Trackable
{
public:
	Level(Grid* pGrid);
	~Level();

	MapWallManager* getMapWalls() { return mpMapWalls; }
	ItemManager* getItemManager() { return mpItemManager; }
	Grid* getGrid() { return mpGrid; }

	void draw(GraphicsBuffer* pBuffer);

private:
	MapWallManager* mpMapWalls;
	ItemManager* mpItemManager;
	Grid* mpGrid;
	//may need gridgraph + other shite
	// EnemySpawner* mpSpawner;


};


class LevelLoader : public Trackable
{
public:
	LevelLoader();
	~LevelLoader() {} ;

	void init();
	void clear();

	Level* getLevel(int index);

private:
	std::vector<Level*> mLevels;
	std::string mFiles[4];
};


