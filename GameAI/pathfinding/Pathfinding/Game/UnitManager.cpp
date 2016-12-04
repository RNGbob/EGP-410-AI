#include "UnitManager.h"
#include "KinematicUnit.h"
#include "SpriteManager.h"
#include "Enemy.h"



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
	
	//delete mPlayerUnit;
	//mPlayerUnit = NULL;

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
	//mPlayerUnit = new KinematicUnit(mpSpriteManager->getSprite(PLAYER_SPRITE_ID), pos, 1, vel, 0.0f, 200.0f, 10.0f);
	//mPlayerUnit->setPlayer();

	// add 16 enemies as object pool. 


}

void UnitManager::cleanup()
{
	
}

void UnitManager::update(float time)
{
	for (int i = 0; i < mUnitList.size(); i++)
	{
		mUnitList[i]->update(time);
	}
	//mPlayerUnit->update(time, mUnitList);
}

void UnitManager::draw(GraphicsBuffer* gBuff)
{
	for (int i = 0; i < mUnitList.size(); i++)
	{
		mUnitList[i]->draw(gBuff);
	}
	//mPlayerUnit->draw(gBuff);
}

void UnitManager::changeVels1(float val)
{
	for (int i = 0; i < mUnitList.size(); i++)
	{
		mUnitList[i]->setMaxVelocity(val);
	}
}

KinematicUnit*  UnitManager::checkAllCollisions(BoxCollider* mBox)
{
	for (int i = 0; i < mUnitList.size(); i++)
	{
		if (mUnitList[i]->getCollider()->checkCollison(mBox))
		{
			return mUnitList[i];
		}
	}
	
	return nullptr;
}


// may replace with object pool of enemies if capped at 4 ghosts
void UnitManager::addUnit(SteeringType steeringType, Vector2D pos, IDType spr)
{
	
	Vector2D vel(0.0f, 0.0f);
	// random sprite of the enemies
	Enemy* newUnit = new Enemy(mpSpriteManager->getSprite(spr), pos, 1, vel, 0.0f, 160.0f, 10.0f);

	mUnitList.push_back(newUnit);

}

// not needed until deletion parameters are known
void UnitManager::deleteUnit(KinematicUnit* unit)
{
	int index;
	for (int i = 0; i < mUnitList.size(); ++i)
	{
		if (unit == mUnitList[i])
		{
			index = i;
			break;
		}
	}
	mUnitList.erase(mUnitList.begin() + index);

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
		//gpGame->endGame();
	}
	
}


