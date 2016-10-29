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
	mApplyDirectly = true;
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

	mpAlign->getSteering();
	mpCohese->getSteering();
	mpSeperate->getSteering();
		
	mLinear += (mpAlign->getLinear()* gpGame->getValue(AlignWeight) ) + 
		(mpCohese->getLinear()*  gpGame->getValue(CohesionWeight)) + 
		(mpSeperate->getLinear()* gpGame->getValue(SeperateWeight)); 

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
			if (gpGame->getUnitManager()->getUnit(i)->getDistance(mpMover) < gpGame->getValue(ReactionRadius))
			{
				return false;
			}
		}
	}
	return true;


}
