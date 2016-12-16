#include "SeekState.h"
#include "Enemy.h"
#include "Player.h"

void SeekState::onEntrance()
{
	mpMover->seek(mpTarget);
	//std::cout << "I see ya" << std::endl;
}

void SeekState::onExit()
{

}

StateTransition * SeekState::update()
{
	
	// if outside of view range transition to wander
	// if powered up transition to flee;
	if (inRange())
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


// bigger range than wander->seek
bool SeekState::inRange()
{
	return mpMover->getLevelIndex() != gpGameA->getCurrentLevelIndex();
}

bool SeekState::PowerUp()
{
	return mpTarget->ifPowered();
}
