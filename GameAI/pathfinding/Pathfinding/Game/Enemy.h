#pragma once
#include "Game.h"
#include "KinematicUnit.h"
#include "StateMachine.h"
#include "LevelLoader.h"


class Enemy : public KinematicUnit
{
public:
	Enemy(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, float maxVelocity, float maxAcceleration);
	~Enemy();

	void update(float time, const std::vector<KinematicUnit*> &units);


private:
	StateMachine* mpStateMachine;
	LevelLoader* mpLevels;
	int mLevelIndex; // for traversing level outside of perspective
	//KinematicUnit* mpPlayer; // will need quick access to player

};