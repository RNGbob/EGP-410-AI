#pragma once
#include "Steering.h"

class KinematicUnit;

const float MAX_WANDER_ROTATION = 1.0f;

class WanderSteering :public Steering
{
public:
	WanderSteering();
	~WanderSteering() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
};