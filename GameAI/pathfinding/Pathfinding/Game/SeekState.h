#pragma once
#include "StateMachine.h"
#include "KinematicUnit.h"

class SeekState : public StateMachineState
{
public:
	SeekState(const SM_idType& id, KinematicUnit* pMover, KinematicUnit* pTarget) 
	:StateMachineState(id),
	mpMover(pMover),
	mpTarget(pTarget) {};


	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();
private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
};