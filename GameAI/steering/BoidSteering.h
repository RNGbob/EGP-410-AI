#pragma once

#include "Steering.h"
#include "AlignmentSteering.h"
#include "CohesionSteering.h"
#include "SeperationSteering.h"
#include <vector>

class KinematicUnit;

class BoidSteering : public Steering
{
public:
	BoidSteering(KinematicUnit* pMover);
	~BoidSteering();

	//void setTarget(KinematicUnit* pTarget) { mpTarget = pTarget; };

	virtual Steering* getSteering();

	bool isFree();// determine if boid is alone or within a group

private:
	KinematicUnit* mpMover;
	AlignmentSteering* mpAlign;
	CohesionSteering* mpCohese;
	SeperationSteering* mpSeperate;


};