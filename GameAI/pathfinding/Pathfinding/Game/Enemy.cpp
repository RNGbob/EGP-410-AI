#include "Enemy.h"
#include "Player.h"
#include "GameApp.h"
#include "WanderState.h"
#include "SeekState.h"
#include "FleeState.h"
#include "DeadState.h"

Enemy::Enemy(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, float maxVelocity, float maxAcceleration)
: KinematicUnit(pSprite, position, orientation, velocity, rotationVel, maxVelocity, maxAcceleration),
mDead(false),
mStarted(false)
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	//mpPlayer = pGame->getPlayerUnit();
	
	// create state machine + transitions here
	mpStateMachine = new StateMachine;

	StateMachineState* pWanderState = new WanderState(0, this, pGame->getPlayerUnit());
	StateMachineState* pSeekState = new SeekState(1, this, pGame->getPlayerUnit());
	StateMachineState* pFleeState = new FleeState(2, this, pGame->getPlayerUnit());
	StateMachineState* pDeadState = new DeadState(3, this, pGame->getPlayerUnit());

	StateTransition* pToWander = new StateTransition(WANDER_TRANSITION,0);
	StateTransition* pToSeek = new StateTransition(SEEK_TRANSITION, 1);
	StateTransition* pToFlee = new StateTransition(FLEE_TRANSITION, 2);
	StateTransition* pToDead = new StateTransition(DEAD_TRANSITION, 3);

	pWanderState->addTransition(pToSeek);
	pWanderState->addTransition(pToFlee);
	pWanderState->addTransition(pToDead);
	pSeekState->addTransition(pToSeek);
	pSeekState->addTransition(pToFlee);
	pSeekState->addTransition(pToDead);
	pFleeState->addTransition(pToWander);
	pFleeState->addTransition(pToSeek);
	pFleeState->addTransition(pToDead);
	pDeadState->addTransition(pToWander);

	mpStateMachine->addState(pWanderState);
	mpStateMachine->addState(pSeekState);
	mpStateMachine->addState(pFleeState);
	mpStateMachine->addState(pDeadState);

	mSpawn = Vector2D(480, 352); // top left center square corner
	mpLevels = pGame->getLevelLoader(); // when exists -_-
	mLevelIndex = pGame->getCurrentLevelIndex();
	inActive();
}

Enemy::~Enemy()
{

}

void Enemy::update(float time)
{
	if (mStarted)
	{
		mpStateMachine->update();
	}
	
	KinematicUnit::update(time);
}

void Enemy::init()
{
	mStarted = true;
}

void Enemy::respawn()
{
	mDead = false;
	mPosition = mSpawn;
}
