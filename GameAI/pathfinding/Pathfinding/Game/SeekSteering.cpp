#include "SeekSteering.h"
#include "GameApp.h"
#include "Enemy.h"
#include "Grid.h"

SeekSteering::SeekSteering( KinematicUnit * pMover, KinematicUnit * pTarget, bool flee)
:mpMover(pMover),
mpTarget(pTarget),
mFlee(flee),
firstPass(true)
{
	mTimer = gpGame->getCurrentTime();
}

Steering * SeekSteering::getSteering()
{
	Enemy* pEnemy = dynamic_cast<Enemy*>(mpMover);
	Grid* pGrid = pEnemy->getLevel()->getGrid();
	static Path followPath;
	static int pathIndex;
	static int toIndex = 0;
	static Vector2D target;
	
	if (firstPass)
	{
		followPath = newPath();
		firstPass = false;
		pathIndex = 1;
		mLinear = Vector2D(0, 0);
		
	}
	
	if (pathIndex+1 < followPath.pathSize() && gpGame->getCurrentTime() - mTimer > 5000)// are we near path end or used one path too long?
	{
		if (toIndex == pGrid->getSquareIndexFromPixelXY( mpMover->getPosition().getX(), mpMover->getPosition().getY()))// are we in our target square?
		{
			pathIndex++;// next node 
		}
		
		toIndex = followPath.peekNode(pathIndex)->getId(); 
		target = pGrid->getULCornerOfSquare(toIndex); // next sqaure in path;
		mLinear = target - mpMover->getPosition();

	}
	else
	{
		followPath = newPath(); //reset path
		pathIndex = 0;
		mTimer = gpGame->getCurrentTime();
	}


	
	/*
	
	if (checkWalls() || )
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
	*/
	mLinear = Vector2D(0, 0);
	if (mFlee)
	{
		mLinear =  mLinear*-1;
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


Path SeekSteering::newPath()
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
		//return path.startingDirection();
	}
	
	return path;
}
