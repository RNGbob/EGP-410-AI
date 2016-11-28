#include "Enemy.h"
#include "GameApp.h"
#include "WanderState.h"
#include "SeekState.h"
#include "FleeState.h"

Enemy::Enemy(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, float maxVelocity, float maxAcceleration)
: KinematicUnit(pSprite, position, orientation, velocity, rotationVel,  maxVelocity,  maxAcceleration)
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	//mpPlayer = pGame->getPlayerUnit();
	
	// create state machine + transitions here
	mpStateMachine = new StateMachine;

	StateMachineState* pWanderState = new WanderState(0, this, pGame->getPlayerUnit());
	StateMachineState* pSeekState = new SeekState(1, this, pGame->getPlayerUnit());
	StateMachineState* pFleeState = new FleeState(2, this, pGame->getPlayerUnit());

	StateTransition* pToWander = new StateTransition(WANDER_TRANSITION,0);
	StateTransition* pToSeek = new StateTransition(SEEK_TRANSITION, 1);
	StateTransition* pToFlee = new StateTransition(FLEE_TRANSITION, 2);

	pWanderState->addTransition(pToSeek);
	pWanderState->addTransition(pToFlee);
	pSeekState->addTransition(pToSeek);
	pSeekState->addTransition(pToFlee);
	pFleeState->addTransition(pToWander);
	pFleeState->addTransition(pToSeek);

	mpStateMachine->addState(pWanderState);
	mpStateMachine->addState(pSeekState);
	mpStateMachine->addState(pFleeState);


	mpLevels = pGame->getLevelLoader(); // when exists -_-
	mLevelIndex = pGame->getCurrentLevelIndex();
}

Enemy::~Enemy()
{
}

void Enemy::update(float time, const std::vector<KinematicUnit*>& units)
{
	mpStateMachine->update();

	KinematicUnit::update(time, units);
}
