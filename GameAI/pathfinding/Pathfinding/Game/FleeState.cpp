#include "FleeState.h"

void FleeState::onEntrance()
{
	mpMover->flee(mpTarget);
	// timer start or access timer in update -_-
}

void FleeState::onExit()
{
}

StateTransition * FleeState::update()
{
	// when power up timer runs out transition to wander, which will seek regardless if close
	
	return nullptr;
}
