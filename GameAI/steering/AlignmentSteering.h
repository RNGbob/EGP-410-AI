#pragma once
#include "Steering.h"
#include <vector>

class KinematicUnit;

class AlignmentSteering : public Steering
{
public:
	AlignmentSteering(KinematicUnit* pMover);
	~AlignmentSteering();

	//void setTarget(KinematicUnit* pTarget) { mpTarget = pTarget; };

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;

};


//https://gamedevelopment.tutsplus.com/tutorials/3-simple-rules-of-flocking-behaviors-alignment-cohesion-and-separation--gamedev-3444