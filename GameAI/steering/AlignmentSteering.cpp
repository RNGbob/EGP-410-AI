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
	//mLinear = Vector2D(0, 0);
	int boidCount = 0;
	for (int i = 0; i < gpGame->getUnitManager()->getSize(); ++i)
	{

		if (gpGame->getUnitManager()->getUnit(i) != mpMover)
		{

			if (gpGame->getUnitManager()->getUnit(i)->getDistance(mpMover) < 200)
			{
				mLinear += gpGame->getUnitManager()->getUnit(i)->getVelocity();
				++boidCount;
			}
		}

	}
	if (boidCount == 0)
	{
		return this;
	}
	mLinear /= boidCount;
	mLinear.normalize();
	//mLinear *= mpMover->getMaxVelocity();
	mAngular = 0;

	return this;



}