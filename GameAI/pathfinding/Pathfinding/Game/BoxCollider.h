#pragma once
#include "Vector2D.h"
#include "Game.h"

class CircleCollider;

class BoxCollider :public Trackable
{
public:
	BoxCollider();
	BoxCollider(Vector2D pos, Vector2D dim);
	~BoxCollider();

	Vector2D getPos()const { return mPos; }
	Vector2D getDim()const { return mDim; }

	void setPos(Vector2D pos) { mPos = pos; }
	bool checkCollison(BoxCollider* &other);
	bool checkCollison(CircleCollider* &other);


private:
	Vector2D mPos, mDim;
};


