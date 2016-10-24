#pragma once

#include "Steering.h"

class KinematicUnit;

class SeperationSteering : public Steering
{
public:
	SeperationSteering(KinematicUnit* pMover, KinematicUnit* pTarget);
	~SeperationSteering();

	void setTarget(KinematicUnit* pTarget) { mpTarget = pTarget; };

	virtual Steering* getSteering();

private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;


};