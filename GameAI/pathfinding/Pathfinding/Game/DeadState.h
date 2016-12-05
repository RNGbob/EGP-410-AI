#pragma once
#include "StateMachine.h"
#include "KinematicUnit.h"
#include "Enemy.h"
#include "Player.h"

class DeadState : public StateMachineState
{
public:
	DeadState(const SM_idType& id, Enemy* pMover, Player* pTarget)
	:StateMachineState(id),
	mpMover(pMover),
	mpTarget(pTarget),
	mRespawnTime(10000) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();

private:
	Enemy* mpMover;
	Player* mpTarget;
	int mRespawnTime;
	int mTimeStart;
};