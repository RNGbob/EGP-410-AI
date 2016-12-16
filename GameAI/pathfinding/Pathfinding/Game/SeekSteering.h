#pragma once
#include "Steering.h"
#include "Game.h"
#include "LevelLoader.h"

class KinematicUnit;


class SeekSteering :public Steering
{
public:
	SeekSteering( KinematicUnit* pMover, KinematicUnit* pTarget, bool flee = false);
	~SeekSteering() {};

	virtual Steering* getSteering();
	bool checkWalls();
	Vector2D newDirection();
	Path newPath();

private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
	Path mfollowPath;
	int mpathIndex;
	int mtoIndex;
	Vector2D mtarget;
	int mTimer;
	bool mFlee;
	bool mDiffLevel;
	bool firstPass;
	bool mPathFound;
};
