#include "Player.h"
#include "GameApp.h"

Player::Player(Sprite * pSprite, const Vector2D & position, float orientation, const Vector2D & velocity, float rotationVel, float maxVelocity, float maxAcceleration)
: KinematicUnit(pSprite, position, orientation, velocity, rotationVel, maxVelocity, maxAcceleration),
mPowerUp(false),
mScore(0)
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);

	mpLevel = pGame->getLevel();
	mpUnitManger = pGame->getUnitManager();
}

void Player::update(float time, const std::vector<KinematicUnit*>& units)
{
	// check wall collisions, if ye stop moving til input changes

	// check item Collisions:
	//if coin increase score/ remove coin
	//if candy start powerup/ remove candy

	// check enemy,  if hit:
	// restart/end
	// if powered up remove enemy.

	//if powered up countdown til end

	
	KinematicUnit::update(time, units);
}

void Player::PowerUp()
{
	mPowerUp = true;
	//start timer
}
