#pragma once
#include "Game.h"
#include "KinematicUnit.h"


class Enemy : public KinematicUnit
{
public:
	Enemy(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, float maxVelocity, float maxAcceleration);
	~Enemy();




private:
	// stateMAchine shite :|

	KinematicUnit* mpPlayer; // will need quick access to player

};