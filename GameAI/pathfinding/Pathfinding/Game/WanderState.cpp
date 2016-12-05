#include "WanderState.h"
#include "Enemy.h"
#include "Player.h"

void WanderState::onEntrance()
{
	mpMover->wander();
	std::cout << "something" << std::endl;
}

void WanderState::onExit()
{
}

StateTransition * WanderState::update()
{
	// if inside view range transition to seek
	// if powered up transition to flee
	if (inRange())
	{
		std::map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(SEEK_TRANSITION);
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
	if (mpMover->isDead())
	{
		std::map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(DEAD_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}

	return nullptr;
}

bool WanderState::inRange()
{
	return false;
}

bool WanderState::PowerUp()
{
	
	return mpTarget->ifPowered();
}
