#include "WanderSteering.h"
#include "KinematicUnit.h"
#include "GameApp.h"
#include "Enemy.h"

WanderSteering::WanderSteering(KinematicUnit * pMover)
:mpMover(pMover)
{
	mTimer = gpGame->getCurrentTime();
	mLinear = newDirection()* mpMover->getMaxVelocity()*.5;

}

Steering * WanderSteering::getSteering()
{
	//GameApp* pGame = dynamic_cast<GameApp*>(gpGame);

	if (checkWalls() ||gpGame->getCurrentTime() - mTimer > 5000)
	{
		if (checkWalls())
		{
			mLinear.normalize();
			mpMover->setPostion(mpMover->getPosition() - (mLinear*10));
			mpMover->setVelocity(Vector2D(0,0));
		}
		mLinear = newDirection()* mpMover->getMaxVelocity()*.5;// *mpMover->getMaxVelocity();
		mTimer = gpGame->getCurrentTime();
	}
	
	
	
	mAngular = 0;
	
	return this;
}

bool WanderSteering::checkWalls()
{
	//Enemy* pEnemy = dynamic_cast<Enemy*>(mpMover);
	mpMover->getCollider()->modPos(mpMover->getdelta()*-1);
	
	
	return mpMover->getEnemyptr()->getLevel()->getMapWalls()->checkCollision(mpMover->getCollider());;
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
		return Vector2D(0, -1);
		break;
	default:
		break;
	}
	
	return Vector2D(0,0);
}
