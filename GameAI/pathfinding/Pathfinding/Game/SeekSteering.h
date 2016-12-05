#pragma once
#include "Steering.h"
#include "Game.h"
#include "LevelLoader.h"

class KinematicUnit;


class SeekSteering :public Steering
{
public:
	SeekSteering( KinematicUnit* pMover, KinematicUnit* pTarget, bool flee = false);
	~SeekSteering() {};

	virtual Steering* getSteering();
	bool checkWalls();
	Vector2D newDirection();

private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
	int mTimer;
	bool mFlee;
};
