#include "SeekSteering.h"
#include "GameApp.h"
#include "Enemy.h"

SeekSteering::SeekSteering( KinematicUnit * pMover, KinematicUnit * pTarget, bool flee)
:mpMover(pMover),
mpTarget(pTarget),
mFlee(flee)
{
	mTimer = gpGame->getCurrentTime();
}

Steering * SeekSteering::getSteering()
{

	if (checkWalls() || gpGame->getCurrentTime() - mTimer > 1000)
	{
		if (checkWalls())
		{
			mpMover->getVelocity().normalize();
			mpMover->setPostion(mpMover->getPosition() - (mpMover->getVelocity()*4));
			mpMover->setVelocity(Vector2D(0, 0));
		}
		mLinear = newDirection() *4;// *mpMover->getMaxVelocity();
		mTimer = gpGame->getCurrentTime();
		if (mFlee)
		{
			mLinear = Vector2D(0,0)-mLinear;
		}
	}

	
	mAngular = 0;
	
	return this;
}

bool SeekSteering::checkWalls()
{
	Enemy* pEnemy = dynamic_cast<Enemy*>(mpMover);
	
	mpMover->getCollider()->modPos(mpMover->getdelta()*-1);

	return pEnemy->getLevel()->getMapWalls()->checkCollision(mpMover->getCollider());;
}

Vector2D SeekSteering::newDirection()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	Enemy* pEnemy = dynamic_cast<Enemy*>(mpMover);
	Path path;
	if (pEnemy->getLevel() == pGame->getLevel())
	{
		path = pEnemy->getLevel()->findPath(mpMover->getPosition() - mpMover->getdelta(), mpTarget->getPosition());
	}
	else
	{
		path = pEnemy->getLevel()->findPath(mpMover->getPosition() - mpMover->getdelta(), Vector2D(-1, -1));
	}

	if (path.pathSize() >= 2)
	{
		return path.startingDirection();
	}

	return Vector2D(0,0);
}
