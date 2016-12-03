#include "WanderState.h"
#include "Enemy.h"
#include "Player.h"

void WanderState::onEntrance()
{
	mpMover->wander();
}

void WanderState::onExit()
{
}

StateTransition * WanderState::update()
{
	Enemy* pEnemy = dynamic_cast<Enemy*>(mpMover);
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
	if (pEnemy->isDead())
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
	Player* pPlayer = dynamic_cast<Player*>(mpMover);

	return pPlayer->ifPowered();
}
