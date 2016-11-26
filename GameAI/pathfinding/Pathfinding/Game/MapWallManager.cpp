#include "MapWallManager.h"
#include "GameApp.h"

MapWallManager::MapWallManager()
{
}

MapWallManager::~MapWallManager()
{
	clear();
}

void MapWallManager::clear()
{
	while (!mpWallBoxes.empty())
	{
		delete mpWallBoxes.back();
		mpWallBoxes.back() = NULL;
		mpWallBoxes.pop_back();

	}

	mpWallBoxes.clear();

}

void MapWallManager::initWalls(Grid * mapGrid)
{
	if (!mpWallBoxes.empty())
	{
		clear();
	}

	BoxCollider* newBox;
	int size = mapGrid->getGridWidth() * mapGrid->getGridHeight();
	//get any non-zero squares and send them to the visualizer
	for (int i = 0; i<size; i++)
	{
		if (mapGrid->getValueAtIndex(i) == 1)
		{
			newBox = new BoxCollider(mapGrid->getULCornerOfSquare(i), Vector2D(GRID_SQUARE_SIZE, GRID_SQUARE_SIZE));
			mpWallBoxes.push_back(newBox);
		}
	}



}
