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
	if (!PowerUp())
	{
		std::map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(WANDER_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	return nullptr;
}

bool FleeState::PowerUp()
{
	return false;
}
