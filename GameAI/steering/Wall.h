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

	bool checkCollision(BoxCollider* unit);
	bool checkCollision(CircleCollider* unit);
	
	void draw();


private:
	Vector2D mStart;
	Vector2D mEnd;
	float mWidth;
	BoxCollider mBox;




};