#pragma once
#include "Vector2D.h"
#include "Game.h"


class BoxCollider :public Trackable
{
public:
	BoxCollider();
	BoxCollider(Vector2D pos, Vector2D dim);
	~BoxCollider();

	Vector2D getPos()const { return mPos; }
	Vector2D getDim()const { return mDim; }

	void setPos(Vector2D pos) { mPos = pos; }
	bool checkBoxCollison(BoxCollider* &other);


private:
	Vector2D mPos, mDim;
};


