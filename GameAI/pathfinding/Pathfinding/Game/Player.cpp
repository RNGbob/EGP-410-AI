#include "Player.h"
#include "GameApp.h"
#include "Enemy.h"

Player::Player(Sprite * pSprite, const Vector2D & position, float orientation, const Vector2D & velocity, float rotationVel, float maxVelocity, float maxAcceleration)
: KinematicUnit(pSprite, position, orientation, velocity, rotationVel, maxVelocity, maxAcceleration),
mPowerUp(false),
mScore(0),
mPUCount(10),
mPUstart(0)
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);

	mpLevel = pGame->getLevel();
	mpUnitManger = pGame->getUnitManager();
}

void Player::update(float time, const std::vector<KinematicUnit*>& units)
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	
	// check wall collisions, if ye stop moving til input changes
	if (mpLevel->getMapWalls()->checkCollision(&mBox))
	{
		mVelocity= Vector2D(0,0);
	}

	// check item Collisions:
	//if coin increase score/ remove coin
	//if candy start powerup/ remove candy
	Candy* candy = pGame->getItemManager()->checkCandy(&mBox);
	if (candy != nullptr)
	{
		PowerUp();
		pGame->getItemManager()->removeCandy(candy);
	}
	Coin* coin = pGame->getItemManager()->checkCoins(&mBox);
	if (coin != nullptr)
	{
		mScore++;
		pGame->getItemManager()->removeCoin(coin);
	}

	// check enemy,  if hit:
	// restart/end
	// if powered up remove enemy.
	KinematicUnit* kUnit = mpUnitManger->checkAllCollisions(&mBox);
	if (kUnit != nullptr)
	{
		if (mPowerUp)
		{
			// or remove enemy unit
			//mpUnitManger->deleteUnit(kUnit);
			Enemy* pEnemy = dynamic_cast<Enemy*>(kUnit);
			pEnemy->kill();
		}
		else
		{
			// some reset
			
		}
	}

	//if powered up countdown til end
	if (mPowerUp)
	{
		if (gpGame->getCurrentTime() - mPUstart >= mPUCount)
		{mPowerUp = false;}
	}
	gpGame->getGraphicsSystem()->wrapCoordinates(mPosition);

	KinematicUnit::update(time, units);
}

void Player::PowerUp()
{
	mPowerUp = true;
	mPUstart = gpGame->getCurrentTime();
}
