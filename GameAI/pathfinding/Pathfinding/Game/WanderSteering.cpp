#include "WanderSteering.h"
#include "KinematicUnit.h"
#include "GameApp.h"
#include "Enemy.h"

WanderSteering::WanderSteering(Level* level,KinematicUnit * pMover)
:mpMover(pMover),
mpLevel(level)
{

}

Steering * WanderSteering::getSteering()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	
	mLinear = Vector2D(0, 0);
	mAngular = 0;
	
	return this;
}

bool WanderSteering::checkWalls()
{
	mpMover->getCollider()->modPos(mpMover->getdelta());
	
	
	return mpLevel->getMapWalls()->checkCollision(mpMover->getCollider());;
}
