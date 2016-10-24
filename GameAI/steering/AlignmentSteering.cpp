#include "AlignmentSteering.h"
#include "KinematicUnit.h"
#include "UnitManager.h"
#include "Game.h"

AlignmentSteering::AlignmentSteering(KinematicUnit * pMover, KinematicUnit * pTarget)
:mpMover(pMover)
, mpTarget(pTarget)
{
}

AlignmentSteering::~AlignmentSteering()
{
}

Steering * AlignmentSteering::getSteering()
{
	
	// blend the 3 steerings together






}
