#include "SeperationSteering.h"
#include "KinematicUnit.h"
#include "UnitManager.h"
#include "Game.h"

SeperationSteering::SeperationSteering(KinematicUnit * pMover, KinematicUnit * pTarget)
{
}

SeperationSteering::~SeperationSteering()
{
}

Steering * SeperationSteering::getSteering()
{
	int boidCount = 0;
	for (int i = 0; i < gpGame->getUnitManager()->getSize(); i++)
	{

		if (gpGame->getUnitManager()->getUnit(i) != mpMover)
		{

			if (gpGame->getUnitManager()->getUnit(i)->getDistance(mpMover) < 500)
			{
				mLinear += gpGame->getUnitManager()->getUnit(i)->getPosition();
				boidCount++;
			}
		}

	}
	mLinear /= boidCount;
	mLinear = Vector2D(mLinear.getX() - mpMover->getPosition().getX(), mLinear.getY() - mpMover->getPosition().getY());
	mLinear *= -1;
	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	mAngular = 0;

	return this;
}
