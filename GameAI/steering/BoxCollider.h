#pragma once
#include "Vector2D.h"
#include "Game.h"


class BoxCollider :public Trackable
{
public:
	BoxCollider();
	BoxCollider(Vector2D pos, Vector2D dim);
	~BoxCollider();


private:
	Vector2D mPos, mDim;
};


