#include "WanderSteering.h"
#include "KinematicUnit.h"
#include "GameApp.h"
#include "Enemy.h"

WanderSteering::WanderSteering(Level* level,KinematicUnit * pMover)
:mpMover(pMover),
mpLevel(level)
{
	mTimer = gpGame->getCurrentTime();


}

Steering * WanderSteering::getSteering()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);

	if (checkWalls() ||gpGame->getCurrentTime() - mTimer > 5000)
	{
		mLinear = newDirection();// *mpMover->getMaxVelocity();
		mTimer = gpGame->getCurrentTime();
	}
	
	
	mAngular = 0;
	
	return this;
}

bool WanderSteering::checkWalls()
{
	mpMover->getCollider()->modPos(mpMover->getdelta());
	
	
	return mpLevel->getMapWalls()->checkCollision(mpMover->getCollider());;
}

Vector2D WanderSteering::newDirection()
{
	int type = rand() % 4;

	switch (type)
	{
	case 0:
		return Vector2D(1, 0);
		break;
	case 1:
		return Vector2D(-1, 0);
		break;
	case 2:
		return Vector2D(0, 1);
		break;
	case 3:
		return Vector2D(0, 1);
		break;
	default:
		break;
	}
	
	return Vector2D(0,0);
}
