#include "WanderState.h"

void WanderState::onEntrance()
{
	mpMover->wander();
}

void WanderState::onExit()
{
}

StateTransition * WanderState::update()
{
	// if inside view range transition to seek
	// if powered up transition to flee
	
	return nullptr;
}
