#pragma once
#include "Steering.h"

class KinematicUnit;

class CohesionSteering : public Steering
{
public:
	CohesionSteering(KinematicUnit* pMover);
	~CohesionSteering();


	virtual Steering* getSteering();

private:
	
	KinematicUnit* mpMover;


};