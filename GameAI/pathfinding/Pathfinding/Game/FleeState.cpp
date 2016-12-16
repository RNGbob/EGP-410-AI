#include "FleeState.h"
#include "Enemy.h"
#include "SpriteManager.h"
#include "GameApp.h"
#include "Player.h"

void FleeState::onEntrance()
{
	mpMover->flee(mpTarget);
	mpMover->switchSprite(gpGame->getSpriteManager()->getSprite(ENEMY_WEAK_SPRITE_ID));
	//std::cout << "REEE" << std::endl;
}

void FleeState::onExit()
{
	mpMover->switchSprite(nullptr);
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

bool FleeState::PowerUp()
{
	
	return mpTarget->ifPowered();
}
