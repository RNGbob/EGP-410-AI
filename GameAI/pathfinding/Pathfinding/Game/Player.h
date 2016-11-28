#pragma once
#include "Game.h"
#include "KinematicUnit.h"
#include "UnitManager.h"
#include "LevelLoader.h"

class Player : public KinematicUnit
{
public:
	Player(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, float maxVelocity, float maxAcceleration);
	~Player() {};

	void setLevel(Level* level) { mpLevel = level; }

	void update(float time, const std::vector<KinematicUnit*> &units);
	void PowerUp();
	

private:
	Level* mpLevel;
	UnitManager* mpUnitManger;
	bool mPowerUp;
	int mScore;
};