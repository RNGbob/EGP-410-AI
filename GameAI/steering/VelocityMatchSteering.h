#pragma once
#include "Steering.h"

class KinematicUnit;

class VelocityMatchSteering : public Steering
{
public:
	VelocityMatchSteering(KinematicUnit* pMover, KinematicUnit* pTarget);
	~VelocityMatchSteering();

	void setTarget(KinematicUnit* pTarget) { mpTarget = pTarget; };

	virtual Steering* getSteering();

private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	 

};