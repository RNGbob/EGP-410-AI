#include "AlignmentSteering.h"
#include "KinematicUnit.h"
#include "UnitManager.h"
#include "Game.h"

AlignmentSteering::AlignmentSteering(KinematicUnit * pMover)
:mpMover(pMover)
{
}

AlignmentSteering::~AlignmentSteering()
{
}

Steering * AlignmentSteering::getSteering()
{
	
	int boidCount = 0;
	for (int i = 0; i < gpGame->getUnitManager()->getSize(); i++)
	{

		if (gpGame->getUnitManager()->getUnit(i) != mpMover)
		{

			if (gpGame->getUnitManager()->getUnit(i)->getDistance(mpMover) < 500)
			{
				mLinear += gpGame->getUnitManager()->getUnit(i)->getVelocity();
				boidCount++;
			}
		}

	}
	mLinear /= boidCount;
	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	mAngular = 0;

	return this;



}
