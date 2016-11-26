#pragma once
#include "Steering.h"

class KinematicUnit;


class SeekSteering :public Steering
{
public:
	SeekSteering(KinematicUnit* pMover, KinematicUnit* pTarget, bool flee = false);
	~SeekSteering() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;

	bool mFlee;
};
