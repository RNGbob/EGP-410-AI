#pragma once

#include "Steering.h"

class KinematicUnit;

class DynamicWanderSeekSteering :public Steering
{
public:
	DynamicWanderSeekSteering(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee = false);
	~DynamicWanderSeekSteering() {};

	void setTarget(KinematicUnit* pTarget) { mpTarget = pTarget; };

	virtual Steering* getSteering();

private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	bool mShouldFlee;
};