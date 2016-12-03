#include "SeekState.h"
#include "Enemy.h"
#include "Player.h"

void SeekState::onEntrance()
{
	mpMover->seek(mpTarget);
}

void SeekState::onExit()
{

}

StateTransition * SeekState::update()
{
	Enemy* pEnemy = dynamic_cast<Enemy*>(mpMover);
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


// bigger range than wander->seek
bool SeekState::inRange()
{
	return false;
}

bool SeekState::PowerUp()
{
	Player* pPlayer = dynamic_cast<Player*>(mpMover);

	return pPlayer->ifPowered();
}
