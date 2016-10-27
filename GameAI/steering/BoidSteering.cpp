#include "BoidSteering.h"
#include "KinematicUnit.h"
#include "UnitManager.h"
#include "KinematicWanderSteering.h"
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
	delete mpAlign;
	delete mpCohese;
	delete mpSeperate;
}

Steering* BoidSteering::getSteering()
{
	//mLinear = Vector2D();

	/*if (isFree())
	{
		// wander
		mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
		mAngular = mpMover->getOrientation() * (genRandomBinomial() * MAX_WANDER_ROTATION);
	}
	else
	{
		
	}*/

	mpAlign->getSteering();
	mpCohese->getSteering();
	mpSeperate->getSteering();
		
	mLinear += (mpAlign->getLinear()* 10 ) + (mpCohese->getLinear()* 5 ) + (mpSeperate->getLinear()* 8 ); // arbitrary vals for now

	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	mAngular = 0;
	
	
	
	return this;
}

bool BoidSteering::isFree()
{
	for (int i = 0; i < gpGame->getUnitManager()->getSize(); i++)
	{
		if (gpGame->getUnitManager()->getUnit(i) != mpMover)
		{
			if (gpGame->getUnitManager()->getUnit(i)->getDistance(mpMover) < 300)
			{
				return false;
			}
		}
	}
	return true;


}
