#pragma once
#include "StateMachine.h"
#include "KinematicUnit.h"
#include "Enemy.h"
#include "Player.h"

class WanderState : public StateMachineState
{
public:
	WanderState(const SM_idType& id, Enemy* pMover, Player* pTarget)
	:StateMachineState(id),
	mpMover(pMover),
	mpTarget(pTarget) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();

	bool inRange();
	bool PowerUp();

private:
	Enemy* mpMover;
	Player* mpTarget;
};