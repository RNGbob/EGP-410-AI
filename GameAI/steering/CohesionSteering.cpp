#include "CohesionSteering.h"
#include "KinematicUnit.h"
#include "UnitManager.h"
#include "Game.h"

CohesionSteering::CohesionSteering(KinematicUnit * pMover)
:mpMover(pMover)

{
}

CohesionSteering::~CohesionSteering()
{
}

Steering * CohesionSteering::getSteering()
{
	mLinear = Vector2D(0, 0);
	int boidCount = 0;
	for (int i = 0; i < gpGame->getUnitManager()->getSize(); ++i)
	{

		if (gpGame->getUnitManager()->getUnit(i) != mpMover)
		{

			if (gpGame->getUnitManager()->getUnit(i)->getDistance(mpMover) < 300)
			{
				mLinear += gpGame->getUnitManager()->getUnit(i)->getPosition();
				++boidCount;
			}
		}

	}
	if (boidCount == 0)
	{
		return this;
	}

	mLinear /= boidCount;
	mLinear -= mpMover->getPosition();
	mLinear.normalize();
	//mLinear *= mpMover->getMaxVelocity();
	mAngular = 0;

	return this;
}
