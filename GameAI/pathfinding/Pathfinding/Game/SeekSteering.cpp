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
	//Enemy* pEnemy = dynamic_cast<Enemy*>(mpMover);
	Grid* pGrid = mpMover->getEnemyptr()->getLevel()->getGrid();
	
	if (firstPass)
	{
		mfollowPath = newPath();
		firstPass = false;
		mpathIndex = 0;
		mtoIndex = mfollowPath.peekNode(mpathIndex)->getId();
		mLinear = Vector2D(0, 0);
		
	}
	
	if (mpathIndex+1 < mfollowPath.pathSize() && gpGame->getCurrentTime() - mTimer < 5000 )// are we near path end or used one path too long?!checkWalls()
	{
		
		if (mtoIndex == pGrid->getSquareIndexFromPixelXY( (mpMover->getPosition() - mpMover->getdelta()).getX() + 2, (mpMover->getPosition() - mpMover->getdelta()).getY() + 2) //pGrid->getULCornerOfSquare(mtoIndex) == mpMover->getPosition()
			&& mtoIndex == pGrid->getSquareIndexFromPixelXY( (mpMover->getPosition() - mpMover->getdelta()).getX() + 30, (mpMover->getPosition() - mpMover->getdelta()).getY() +30)
			)// are we in our target square? 							   
			
		{
			mpathIndex++;// next node 
		}
		//std::cout << mtoIndex  
		//<< "   " << pGrid->getSquareIndexFromPixelXY((mpMover->getPosition() - mpMover->getdelta()).getX() +2 , (mpMover->getPosition() - mpMover->getdelta()).getY() +2 )
		//<< "   " << pGrid->getSquareIndexFromPixelXY((mpMover->getPosition() - mpMover->getdelta()).getX() + 28, (mpMover->getPosition() - mpMover->getdelta()).getY() + 28) << std::endl;
		mtoIndex = mfollowPath.peekNode(mpathIndex)->getId(); 
		mtarget = pGrid->getULCornerOfSquare(mtoIndex) ; // next sqaure in path;
		mLinear = mtarget - mpMover->getPosition();//pGrid->getULCornerOfSquare(pGrid->getSquareIndexFromPixelXY(mpMover->getPosition().getX() , mpMover->getPosition().getY() ));// +Vector2D(-32, -32);

	}
	else
	{ 
		//reset path
		mfollowPath = newPath();
		if (mfollowPath.pathSize() > 0)
		{
			mpathIndex = 0;
			mtoIndex = mfollowPath.peekNode(mpathIndex)->getId();
		}
		mTimer = gpGame->getCurrentTime();
		//mLinear = Vector2D(0, 0);
	}


	if (mFlee)
	{
		mLinear =  mLinear*-1;
	}
	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	mAngular = 0;
	
	return this;
}

bool SeekSteering::checkWalls()
{
	//Enemy* pEnemy = dynamic_cast<Enemy*>(mpMover);
	
	mpMover->getCollider()->modPos(mpMover->getdelta()*-1);

	return mpMover->getEnemyptr()->getLevel()->getMapWalls()->checkCollision(mpMover->getCollider());;
}

Vector2D SeekSteering::newDirection()
{
	//GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	//Enemy* = dynamic_cast<Enemy*>(mpMover);
	Path path;
	if (mpMover->getEnemyptr()->getLevel() == gpGameA->getLevel())
	{
		path = mpMover->getEnemyptr()->getLevel()->findPath(mpMover->getPosition() - mpMover->getdelta(), mpTarget->getPosition());
	}
	else
	{
		path = mpMover->getEnemyptr()->getLevel()->findPath(mpMover->getPosition() - mpMover->getdelta(), Vector2D(-1, -1));
	}

	if (path.pathSize() >= 2)
	{
		return path.startingDirection();
	}

	return Vector2D(0,0);
}


Path SeekSteering::newPath()
{
	//GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	//Enemy* = dynamic_cast<Enemy*>(mpMover);
	Path path;
	if (mpMover->getEnemyptr()->getLevel() == gpGameA->getLevel())
	{
		path = mpMover->getEnemyptr()->getLevel()->findPath(mpMover->getPosition() - mpMover->getdelta(), mpTarget->getPosition());
	}
	else
	{
		path = mpMover->getEnemyptr()->getLevel()->findPath(mpMover->getPosition() - mpMover->getdelta(), Vector2D(-1, -1));
	}

	
	
	return path;
}
