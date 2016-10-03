#include "DynamicWanderSeekSteering.h"
#include "KinematicWanderSteering.h"
#include "KinematicUnit.h"
#include "Game.h"

DynamicWanderSeekSteering::DynamicWanderSeekSteering(KinematicUnit *pMover, KinematicUnit* pTarget, bool shouldFlee)
	:mpMover(pMover)
	, mpTarget(pTarget)
	, mShouldFlee(shouldFlee)
{
	mApplyDirectly = false;
}

Steering* DynamicWanderSeekSteering::getSteering()
{
	float xLength = mpTarget->getPosition().getX() - mpMover->getPosition().getX();
	float yLength = mpTarget->getPosition().getY() - mpMover->getPosition().getY();
	
	if (abs(sqrt(yLength*yLength*xLength*xLength)) < gpGame->getValue(ReactionRadius)) // arbitrary for now
	{

		if (!mShouldFlee)
		{mLinear = mpTarget->getPosition() - mpMover->getPosition();}
		else
		{mLinear = mpMover->getPosition() - mpTarget->getPosition();}

		mLinear.normalize();
		mLinear *= mpMover->getMaxVelocity();
		mAngular = 0;

	}		
	else
	{
		mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity(); 
		mAngular = mpMover->getOrientation() * (genRandomBinomial() * MAX_WANDER_ROTATION);
	}
	
	
	return this;
}


