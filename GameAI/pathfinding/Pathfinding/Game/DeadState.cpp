#include "DeadState.h"
#include "Enemy.h"

void DeadState::onEntrance()
{
	mpMover->inActive();
	mTimeStart = gpGame->getCurrentTime();
	//std::cout << "Blarg, I'm dead" << std::endl;
}

void DeadState::onExit()
{
	
	mpMover->respawn();
}

StateTransition * DeadState::update()
{
	if (gpGame->getCurrentTime() - mTimeStart >= mRespawnTime)
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
