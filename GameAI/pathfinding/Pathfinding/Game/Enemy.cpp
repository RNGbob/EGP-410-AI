#include "Enemy.h"
#include "Player.h"
#include "GameApp.h"
#include "SpriteManager.h"
#include "WanderState.h"
#include "SeekState.h"
#include "FleeState.h"
#include "DeadState.h"

Enemy::Enemy(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, float maxVelocity, float maxAcceleration)
: KinematicUnit(pSprite, position, orientation, velocity, rotationVel, maxVelocity, maxAcceleration),
mDead(false),
mStarted(false)
{
	//GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	mpEnemyptr = this;

	//mpPlayer = pGame->getPlayerUnit();
	mpNormSprite = pSprite;
	// create state machine + transitions here
	mpStateMachine = new StateMachine;

	StateMachineState* pWanderState = new WanderState(0, this, gpGameA->getPlayerUnit());
	StateMachineState* pSeekState = new SeekState(1, this, gpGameA->getPlayerUnit());
	StateMachineState* pFleeState = new FleeState(2, this, gpGameA->getPlayerUnit());
	StateMachineState* pDeadState = new DeadState(3, this, gpGameA->getPlayerUnit());

	StateTransition* pToWander = new StateTransition(WANDER_TRANSITION,0);
	StateTransition* pToSeek = new StateTransition(SEEK_TRANSITION, 1);
	StateTransition* pToFlee = new StateTransition(FLEE_TRANSITION, 2);
	StateTransition* pToDead = new StateTransition(DEAD_TRANSITION, 3);

	pWanderState->addTransition(pToSeek);
	pWanderState->addTransition(pToFlee);
	pWanderState->addTransition(pToDead);
	pWanderState->addTransition(pToWander); //needed so destructors delete the transitions only once;
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

	mpStateMachine->setInitialStateID(0);

	 // top left center square corner
	mpLevels = gpGameA->getLevelLoader(); // when exists -_-
	mLevelIndex = gpGameA->getCurrentLevelIndex();
	//mSpawn = mpLevels
	inActive();
}

Enemy::~Enemy()
{
	delete mpStateMachine;
	mpStateMachine = NULL;
}

void Enemy::update(float time)
{
	if (mStarted)
	{
		mpStateMachine->update();
	}
	checkBounds();
	KinematicUnit::update(time);
}

void Enemy::init()
{
	//GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	mStarted = true;
	mActive = true;
	mLevelIndex = gpGameA->getCurrentLevelIndex();
	mSpawn = getLevel()->getGrid()->getULCornerOfSquare((32 * 12) + 16);// +Vector2D(2, 2);
	respawn();
}

void Enemy::respawn()
{
	mDead = false;
	mDeltaPosition = Vector2D(0, 0);
	mPosition = mSpawn;

	 // reset level index
}

void Enemy::checkBounds()
{
	
	float x = mPosition.getX() - mDeltaPosition.getX();
	float y = mPosition.getY() - mDeltaPosition.getY();

	switch (mLevelIndex)
	{
	case 0: // 1
		if (x > WIDTH) // going to 2
		{
			mLevelIndex = 1;
			mDeltaPosition+= Vector2D(WIDTH, 0);
		}
		if (y > HEIGHT) //going to 3
		{
			mLevelIndex = 2;
			mDeltaPosition += Vector2D(0, HEIGHT);
		}
		if (x < 0) // nowhere
		{
			//stop();
		}
		if (y < 0) // nowhere
		{
			//stop();
		}
		break;
	case 1: // 2
		if (x < 0) // going to 1
		{
			mLevelIndex = 0;
			mDeltaPosition += Vector2D(-WIDTH, 0);
		}
		if (y > HEIGHT) // going to 4
		{
			mLevelIndex = 3;
			mDeltaPosition += Vector2D(0, HEIGHT);
		}
		if (x > WIDTH - GRID_SQUARE_SIZE) // nowhere
		{
			//stop();
		}
		if (y < 0) //nowhere
		{
			//stop();
		}
		break;
	case 2: // 3
		if (x > WIDTH) // going to 4
		{
			mLevelIndex = 3;
			mDeltaPosition += Vector2D(WIDTH, 0);
		}
		if (y < 0) // going to 1
		{
			mLevelIndex = 0;
			mDeltaPosition += Vector2D(0, -HEIGHT);
		}
		if (x < 0) // nowhere
		{
			//stop();
		}
		if (y > HEIGHT - GRID_SQUARE_SIZE) // nowhere
		{
			//stop();
		}
		break;
	case 3: // 4
		if (x < 0) // going to 3
		{
			mLevelIndex = 2;
			mDeltaPosition += Vector2D(-WIDTH, 0);
		}
		if (y < 0) // going to 2
		{
			mLevelIndex = 1;
			mDeltaPosition += Vector2D(0, -HEIGHT);
		}
		if (x > WIDTH - GRID_SQUARE_SIZE) // nowhere
		{
			//stop();
		}
		if (y > HEIGHT - GRID_SQUARE_SIZE) // nowhere
		{
			//stop();
		}
		break;
	default:
		break;
	}
}


