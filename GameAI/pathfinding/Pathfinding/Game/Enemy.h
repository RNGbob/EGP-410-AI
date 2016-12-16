#pragma once
#include "Game.h"
#include "KinematicUnit.h"
#include "StateMachine.h"
#include "LevelLoader.h"


class Enemy : public KinematicUnit
{
public:
	Enemy(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, float maxVelocity, float maxAcceleration);
	virtual ~Enemy();

	virtual void update(float time);
	void init();
	void respawn();
	bool isDead() { return mDead; }
	void kill() { mDead = true; }
	Level* getLevel() { return mpLevels->getLevel(mLevelIndex); }
	int getLevelIndex() { return mLevelIndex; }
	void checkBounds();

private:
	StateMachine* mpStateMachine;
	LevelLoader* mpLevels;
	Vector2D mSpawn;
	int mLevelIndex; // for traversing level outside of perspective
	bool mDead;
	bool mStarted;
};