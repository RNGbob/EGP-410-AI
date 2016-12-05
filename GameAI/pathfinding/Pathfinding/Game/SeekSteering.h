#pragma once
#include "Steering.h"
#include "LevelLoader.h"

class KinematicUnit;


class SeekSteering :public Steering
{
public:
	SeekSteering(Level* lev, KinematicUnit* pMover, KinematicUnit* pTarget, bool flee = false);
	~SeekSteering() {};

	virtual Steering* getSteering();
	bool checkWalls();

private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
	Level* mpLevel;
	int PFtimer;
	bool mFlee;
};
