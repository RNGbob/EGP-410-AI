#pragma once

#include "Steering.h"

class KinematicUnit;

class SeperationSteering : public Steering
{
public:
	SeperationSteering(KinematicUnit* pMover);
	~SeperationSteering();

	

	virtual Steering* getSteering();

private:

	KinematicUnit* mpMover;


};