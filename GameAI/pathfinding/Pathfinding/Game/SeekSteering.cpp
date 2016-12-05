#include "SeekSteering.h"
#include "GameApp.h"
#include "Enemy.h"

SeekSteering::SeekSteering(Level* lev, KinematicUnit * pMover, KinematicUnit * pTarget, bool flee)
:mpMover(pMover),
mpTarget(pTarget),
mFlee(flee),
mpLevel(lev)
{
}

Steering * SeekSteering::getSteering()
{
	

	mLinear = Vector2D(0, 0);
	mAngular = 0;
	
	return this;
}

bool SeekSteering::checkWalls()
{
	mpMover->getCollider()->modPos(mpMover->getdelta());


	return mpLevel->getMapWalls()->checkCollision(mpMover->getCollider());;
}
