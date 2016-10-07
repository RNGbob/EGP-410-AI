#pragma once


#include "GraphicsSystem.h"
#include "Game.h"
#include <vector>

class Wall;


class WallManager : public Trackable
{
public:
	WallManager();
	~WallManager();

	void draw();
	void addWall();
	bool checkCollision(KinematicUnit* unit);

private:

	std::vector < Wall*> mWalls;


};