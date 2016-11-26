#include "SeekSteering.h"

SeekSteering::SeekSteering(KinematicUnit * pMover, KinematicUnit * pTarget, bool flee)
:mpMover(pMover),
mpTarget(pTarget),
mFlee(flee)
{
}

Steering * SeekSteering::getSteering()
{
	return nullptr;
}
