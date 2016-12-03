#include "FleeState.h"
#include "Enemy.h"
#include "GameApp.h"
#include "Player.h"

void FleeState::onEntrance()
{
	mpMover->flee(mpTarget);
}

void FleeState::onExit()
{
}

StateTransition * FleeState::update()
{
	Enemy* pEnemy = dynamic_cast<Enemy*>(mpMover);
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

bool FleeState::PowerUp()
{
	Player* pPlayer = dynamic_cast<Player*>(mpMover);
	
	
	return pPlayer->ifPowered();
}
