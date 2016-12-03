#include "DeadState.h"
#include "Enemy.h"

void DeadState::onEntrance()
{
	mpMover->inActive();
	mTimeStart = gpGame->getCurrentTime();
}

void DeadState::onExit()
{
	Enemy* pEnemy = dynamic_cast<Enemy*>(mpMover);
	pEnemy->respawn();
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
