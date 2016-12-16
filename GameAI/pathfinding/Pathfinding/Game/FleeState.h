#pragma once
#include "StateMachine.h"
#include "KinematicUnit.h"
#include "Enemy.h"
#include "Player.h"

class FleeState : public StateMachineState
{
public:
	FleeState(const SM_idType& id, Enemy* pMover, Player* pTarget)
	:StateMachineState(id),  
	mpMover(pMover),
	mpTarget(pTarget) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();

	bool PowerUp();

private:
	Enemy* mpMover;
	Player* mpTarget;

};