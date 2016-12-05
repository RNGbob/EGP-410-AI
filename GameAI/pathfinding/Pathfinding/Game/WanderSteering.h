#pragma once
#include "Steering.h"

class KinematicUnit;

const float MAX_WANDER_ROTATION = 1.0f;

class WanderSteering :public Steering
{
public:
	WanderSteering(Level* lev, KinematicUnit* pMover);
	~WanderSteering() {};

	virtual Steering* getSteering();
	bool checkWalls();

private:
	KinematicUnit* mpMover;
	Level* mpLevel;
};