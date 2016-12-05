#include "SeekSteering.h"
#include "GameApp.h"
#include "Enemy.h"

SeekSteering::SeekSteering(Level* lev, KinematicUnit * pMover, KinematicUnit * pTarget, bool flee)
:mpMover(pMover),
mpTarget(pTarget),
mFlee(flee),
mpLevel(lev)
{
	mTimer = gpGame->getCurrentTime();
}

Steering * SeekSteering::getSteering()
{

	if (checkWalls() || gpGame->getCurrentTime() - mTimer > 1000)
	{
		mLinear = newDirection();// *mpMover->getMaxVelocity();
		mTimer = gpGame->getCurrentTime();
	}
	if (mFlee)
	{
		mLinear = Vector2D(0,0)-mLinear;
	}
	
	mAngular = 0;
	
	return this;
}

bool SeekSteering::checkWalls()
{
	mpMover->getCollider()->modPos(mpMover->getdelta());


	return mpLevel->getMapWalls()->checkCollision(mpMover->getCollider());;
}

Vector2D SeekSteering::newDirection()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	Path path;
	if (mpLevel!= pGame->getLevel())
	{
		path = mpLevel->findPath(mpMover->getPosition() + mpMover->getPosition(), mpTarget->getPosition());
	}
	else
	{
		path = mpLevel->findPath(mpMover->getPosition() + mpMover->getPosition(), Vector2D(-1, -1));
	}

	if (path.pathSize() >= 2)
	{
		return path.startingDirection();
	}

	return Vector2D(0,0);
}
