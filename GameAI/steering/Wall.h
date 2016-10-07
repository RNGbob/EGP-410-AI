#pragma once

#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Game.h"
#include "KinematicUnit.h"


class Wall :public Trackable
{
public:
	Wall();
	Wall(Vector2D start, Vector2D end, float width);
	~Wall();

	bool checkCollision(KinematicUnit* unit);
	
	void draw();


private:
	Vector2D mStart;
	Vector2D mEnd;
	Vector2D mCorner;
	Vector2D mDim;
	float mWidth;





};