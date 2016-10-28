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

	bool checkCollision(BoxCollider* unit);
	bool checkCollision(CircleCollider* unit);

	void draw();


private:
	Vector2D mPos;
	float mRadius;
	CircleCollider mCircle;




};