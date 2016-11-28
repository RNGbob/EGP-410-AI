#include "SeekState.h"

void SeekState::onEntrance()
{
	mpMover->seek(mpTarget);
}

void SeekState::onExit()
{

}

StateTransition * SeekState::update()
{
	// if outside of view range transition to wander
	// if powered up transition to flee;
	if (false)
	{
		std::map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(WANDER_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	if (PowerUp())
	{
		std::map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(FLEE_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	
	return nullptr;
}


// bigger range than wander->seek
bool SeekState::inRange()
{
	return false;
}

bool SeekState::PowerUp()
{
	return false;
}
