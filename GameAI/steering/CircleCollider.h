#pragma once
#include "Vector2D.h"
#include "Game.h"

class BoxCollider;

class CircleCollider :public Trackable
{
public:
	CircleCollider();
	CircleCollider(Vector2D pos, float radius);
	~CircleCollider();

	Vector2D getPos()const { return mPos; }
	float getRadius()const { return mRadius; }

	void setPos(Vector2D pos) { mPos = pos; }
	bool checkCollison(BoxCollider* &other);
	bool checkCollison(CircleCollider* &other);


private:
	Vector2D mPos;
	float mRadius;
};
