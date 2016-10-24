#pragma once
#include "Steering.h"

class KinematicUnit;

class CohesionSteering : public Steering
{
public:
	CohesionSteering(KinematicUnit* pMover, KinematicUnit* pTarget);
	~CohesionSteering();

	void setTarget(KinematicUnit* pTarget) { mpTarget = pTarget; };

	virtual Steering* getSteering();

private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;


};