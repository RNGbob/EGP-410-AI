#include "Player.h"
#include "Game.h"
#include "GameApp.h"
#include "Enemy.h"

Player::Player(Sprite * pSprite, const Vector2D & position, float orientation, const Vector2D & velocity, float rotationVel, float maxVelocity, float maxAcceleration)
: KinematicUnit(pSprite, position, orientation, velocity, rotationVel, maxVelocity, maxAcceleration),
mPowerUp(false),
mScore(0),
mPUCount(10),
mPUstart(0)
{
	setPlayer();
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);

	mpLevel = pGame->getLevel();
	mpUnitManger = pGame->getUnitManager();
}

void Player::update(float time)
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	
	// check wall collisions, if ye stop moving til input changes
	if (mpLevel->getMapWalls()->checkCollision(&mBox) && mVelocity != Vector2D(0,0))
	{
		stop();
	}

	// check item Collisions:
	//if coin increase score/ remove coin
	//if candy start powerup/ remove candy
	Candy* candy = pGame->getItemManager()->checkCandy(&mBox);
	if (candy != nullptr)
	{
		PowerUp();
		std::cout << "BOOM" << std::endl;
		pGame->getItemManager()->removeCandy(candy);
	}
	Coin* coin = pGame->getItemManager()->checkCoins(&mBox);
	if (coin != nullptr)
	{
		mScore++;
		//std::cout << "CREAM" << std::endl;
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
	//gpGame->getGraphicsSystem()->wrapCoordinates(mPosition);

	checkBounds(pGame->getCurrentLevelIndex(), pGame);

	KinematicUnit::update(time);
}

void Player::PowerUp()
{
	mPowerUp = true;
	mPUstart = gpGame->getCurrentTime();
}

void Player::checkBounds(int levelIndex, GameApp* pGame)
{
	/*
	
	Map Layout
	|  1  |  2  |
	|  3  |  4  |
	
	*/
	
	float x = mPosition.getX();
	float y = mPosition.getY();

	switch (levelIndex)
	{
	case 0: // 1
		if (x > WIDTH ) // going to 2
		{
			gpGame->getGraphicsSystem()->wrapCoordinates(mPosition);
			mpLevel = pGame->switchLevel(1);
		}
		if (y > HEIGHT) //going to 3
		{
			gpGame->getGraphicsSystem()->wrapCoordinates(mPosition);
			mpLevel = pGame->switchLevel(2);
		}
		if (x < 0) // nowhere
		{stop();}
		if (y < 0) // nowhere
		{stop();}
		break;
	case 1: // 2
		if (x < 0) // going to 1
		{
			gpGame->getGraphicsSystem()->wrapCoordinates(mPosition);
			mpLevel = pGame->switchLevel(0);
		}
		if (y > HEIGHT) // going to 4
		{
			gpGame->getGraphicsSystem()->wrapCoordinates(mPosition);
			mpLevel = pGame->switchLevel(3);
		}
		if (x > WIDTH) // nowhere
		{stop();}
		if (y < 0) //nowhere
		{stop();}
		break;
	case 2: // 3
		if (x > WIDTH) // going to 4
		{
			gpGame->getGraphicsSystem()->wrapCoordinates(mPosition);
			mpLevel = pGame->switchLevel(3);
		}
		if (y < 0) // going to 1
		{
			gpGame->getGraphicsSystem()->wrapCoordinates(mPosition);
			mpLevel = pGame->switchLevel(0);
		}
		if (x < 0) // nowhere
		{stop();}
		if (y > HEIGHT) // nowhere
		{stop();}
		break;
	case 3: // 4
		if (x < 0) // going to 3
		{
			gpGame->getGraphicsSystem()->wrapCoordinates(mPosition);
			mpLevel = pGame->switchLevel(2);
		}
		if (y < 0) // going to 2
		{
			gpGame->getGraphicsSystem()->wrapCoordinates(mPosition);
			mpLevel = pGame->switchLevel(1);
		}
		if (x > WIDTH) // nowhere
		{stop();}
		if (y > HEIGHT) // nowhere
		{stop();}
		break;
	default:
		break;
	}



}

void Player::stop()
{
	mVelocity.normalize();
	mPosition = mPosition - mVelocity;
	mVelocity = Vector2D(0, 0);
}
