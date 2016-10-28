#include "UnitManager.h"
#include "KinematicUnit.h"
#include "SpriteManager.h"
#include "WallManager.h"


UnitManager::UnitManager()
{

}

UnitManager::~UnitManager()
{
	
	while (!mUnitList.empty())
	{
		delete mUnitList.back();
		mUnitList.back() = NULL;
		mUnitList.pop_back();
	}
	
	mUnitList.clear();
	
	delete mPlayerUnit;
	mPlayerUnit = NULL;

	//delete mpSpriteManager;
	mpSpriteManager = NULL;
}

void UnitManager::init( SpriteManager* &mpSprMan)
{
	// spriteManager
	mpSpriteManager = mpSprMan;

	// create plater unit
	Vector2D pos(100.0f, 100.0f);
	Vector2D vel(0.0f, 0.0f);
	mPlayerUnit = new KinematicUnit(mpSpriteManager->getSprite(PLAYER_ICON_SPRITE_ID), pos, 1, vel, 0.0f, 200.0f, 10.0f);
	mPlayerUnit->setPlayer();
}

void UnitManager::cleanup()
{
	/*/
	for ( std::vector<KinematicUnit*>::iterator it = mUnitList.begin();  it !=mUnitList.end(); ++it)
	{
		delete *it;
	}/**/
	

}

void UnitManager::update(float time)
{
	for (int i = 0; i < mUnitList.size(); i++)
	{
		mUnitList[i]->update(time, mUnitList);
	}
	mPlayerUnit->update(time, mUnitList);
}

void UnitManager::draw(GraphicsBuffer* gBuff)
{
	for (int i = 0; i < mUnitList.size(); i++)
	{
		mUnitList[i]->draw(gBuff);
	}
	mPlayerUnit->draw(gBuff);
}

void UnitManager::changeVels1(float val)
{
	for (int i = 0; i < mUnitList.size(); i++)
	{
		mUnitList[i]->setMaxVelocity(val);
	}
}



void UnitManager::addUnit(Method steeringType)
{
	double theta = rand() % 360;//2*PI;
	
	Vector2D pos(mPlayerUnit->getPosition().getX() + (100 * sin(theta)), mPlayerUnit->getPosition().getY() + (100 * cos(theta))); 
	

	Vector2D vel(0.0f, 0.0f);
	KinematicUnit* newUnit;

	switch (steeringType)
	{
	case Boids:
		newUnit = new KinematicUnit(mpSpriteManager->getSprite(AI_ICON_SPRITE_ID), pos, 1, vel, 10.0f, gpGame->getValue(EnemyVel), 50.f);
		newUnit->boid(mPlayerUnit);
		mUnitList.push_back(newUnit);
		break;
	case WanderSeek:
		newUnit = new KinematicUnit(mpSpriteManager->getSprite(AI_ICON_SPRITE_ID), pos, 1, vel, 10.0f, gpGame->getValue(EnemyVel), 50.f);
		newUnit->wanderSeek(mPlayerUnit);
		mUnitList.push_back(newUnit);
		break;
	case WanderFlee:
		newUnit = new KinematicUnit(mpSpriteManager->getSprite(AI_ICON_SPRITE_ID), pos, 1, vel, 10.0f, gpGame->getValue(EnemyVel), 50.0f);
		newUnit->wanderFlee(mPlayerUnit);
		mUnitList.push_back(newUnit);
		break;
	default:
		break;
	}
	
	/*
	*/

	


}

// not needed until deletion parameters are known
void UnitManager::deleteUnit()
{

}

void UnitManager::deleteRandomUnit()
{
	

	if (!mUnitList.empty())
	{
	int index = rand() % (mUnitList.size());
	delete mUnitList[index];
	mUnitList[index] = NULL;
	
	mUnitList.erase(mUnitList.begin() + index);
	}
	else
	{
		gpGame->endGame();
	}
	
}


