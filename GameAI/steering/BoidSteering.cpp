#include "BoidSteering.h"
#include "KinematicUnit.h"
#include "UnitManager.h"
#include "Game.h"

BoidSteering::BoidSteering(KinematicUnit * pMover)
	:mpMover(pMover)
{
	mpAlign = new AlignmentSteering(mpMover);
	mpCohese = new CohesionSteering(mpMover);
	mpSeperate = new SeperationSteering(mpMover);

}

BoidSteering::~BoidSteering()
{
}

Steering* BoidSteering::getSteering()
{
	
	
	if (false)
	{
		// wander
	}
	else
	{
		

		mLinear += (mpAlign->getSteering()->getLinear()* 1 ) + (mpCohese->getSteering()->getLinear()* 2 ) + (mpSeperate->getSteering()->getLinear()* 3 ); // arbitrary vals for now


	}

	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	mAngular = 0;
	
	
	
	return this;
}

bool BoidSteering::isFree()
{
	return false;
}
