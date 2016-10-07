#include "WallManager.h"
#include "Wall.h"

WallManager::WallManager()
{
}

WallManager::~WallManager()
{
	while (!mWalls.empty())
	{
		delete mWalls.back();
		mWalls.back() = NULL;
		mWalls.pop_back();
	}
}

void WallManager::draw()
{
	for each (Wall* wall in mWalls)
	{
		wall->draw();
	}
}

void WallManager::addWall(Vector2D start, Vector2D end, float width)
{
	Wall* newWall = new Wall(start, end, width);
	mWalls.push_back(newWall);
}

bool WallManager::checkCollision(KinematicUnit * unit)
{
	bool collision =false;

	for each (Wall* wall in mWalls)
	{
		collision = wall->checkCollision(unit);
		if (collision) { break; }
	}
	
	
	return collision;
}
