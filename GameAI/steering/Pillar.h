#pragma once
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Game.h"
#include "KinematicUnit.h"


class Pillar :public Trackable
{
public:
	Pillar();
	Pillar(Vector2D pos, float radius);
	~Pillar();

	Vector2D getPos()const { return mPos; }
	float getRadius()const { return mRadius; }

	bool checkCollision(BoxCollider* unit);
	bool checkCollision(CircleCollider* unit);

	void draw();


private:
	Vector2D mPos;
	float mRadius;
	CircleCollider mCircle;




};