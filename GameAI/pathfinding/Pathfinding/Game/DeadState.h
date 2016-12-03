#pragma once
#include "StateMachine.h"
#include "KinematicUnit.h"

class DeadState : public StateMachineState
{
public:
	DeadState(const SM_idType& id, KinematicUnit* pMover, KinematicUnit* pTarget)
	:StateMachineState(id),
	mpMover(pMover),
	mpTarget(pTarget),
	mRespawnTime(10) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();

private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
	int mRespawnTime;
	int mTimeStart;
};