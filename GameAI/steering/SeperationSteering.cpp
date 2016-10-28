#include "SeperationSteering.h"
#include "KinematicUnit.h"
#include "UnitManager.h"
#include "Game.h"

SeperationSteering::SeperationSteering(KinematicUnit * pMover)
:mpMover(pMover)

{
}

SeperationSteering::~SeperationSteering()
{
}

Steering * SeperationSteering::getSteering()
{
	mLinear = Vector2D(0, 0);
	int boidCount = 0;
	for (int i = 0; i < gpGame->getUnitManager()->getSize(); ++i)
	{

		if (gpGame->getUnitManager()->getUnit(i) != mpMover)
		{

			if (gpGame->getUnitManager()->getUnit(i)->getDistance(mpMover) < 50)
			{
				mLinear += ( gpGame->getUnitManager()->getUnit(i)->getPosition() - mpMover->getPosition()) * max( (100 / gpGame->getUnitManager()->getUnit(i)->getDistance(mpMover)),1);
				boidCount++;
			}
		}

	}
	if (boidCount == 0)
	{
		return this;
	}

	mLinear /= boidCount;
	//mLinear -= mpMover->getPosition(); 
	mLinear *= -1;
	mLinear.normalize();
	//mLinear *= mpMover->getMaxVelocity();
	mAngular = 0;

	return this;
}
