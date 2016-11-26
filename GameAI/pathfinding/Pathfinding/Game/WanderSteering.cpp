#include "WanderSteering.h"
#include "KinematicUnit.h"

WanderSteering::WanderSteering(KinematicUnit * pMover)
:mpMover(pMover)
{

}

Steering * WanderSteering::getSteering()
{
	return nullptr;
}
