#pragma once


#include "GraphicsSystem.h"
#include "Game.h"
#include "Wall.h"
#include <vector>

class Wall;


class WallManager : public Trackable
{
public:
	WallManager();
	~WallManager();

	void draw();
	void addWall(Vector2D start, Vector2D end, float width);
	bool checkCollision(BoxCollider* unit);

private:

	std::vector < Wall*> mWalls;


};