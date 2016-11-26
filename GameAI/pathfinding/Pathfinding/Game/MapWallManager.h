#pragma once
#include "Game.h"
#include "BoxCollider.h"
#include "Grid.h"
#include <vector>

class MapWallManager : public Trackable
{
public:
	MapWallManager();
	~MapWallManager();

	void clear();
	void initWalls(Grid* mapGrid);

private:
	std::vector<BoxCollider*> mpWallBoxes;

};
