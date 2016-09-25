#include "UnitManager.h"
#include "KinematicUnit.h"
#include "SpriteManager.h"


UnitManager::UnitManager()
{

}

UnitManager::~UnitManager()
{

}

void UnitManager::init(const IDType &playerID, const IDType &enemyID,  SpriteManager* &mpSprMan)
{
	// spriteManager
	mpSpriteManager = mpSprMan;
	mEnemyID = enemyID;
	
	
	// create plater unit
	Vector2D pos(0.0f, 0.0f);
	Vector2D vel(0.0f, 0.0f);
	mPlayerUnit = new KinematicUnit(mpSpriteManager->getSprite(playerID), pos, 1, vel, 0.0f, 200.0f, 10.0f);
}

void UnitManager::cleanup()
{
	while (!mUnitList.empty())
	{
		delete mUnitList.back();
		mUnitList.back() = NULL;
		mUnitList.pop_back();
	}

	delete mPlayerUnit;
	mPlayerUnit = NULL;

	delete mpSpriteManager;
	mpSpriteManager = NULL;

}

void UnitManager::update(float time)
{
	for (int i = 0; i < mUnitList.size(); i++)
	{
		mUnitList[i]->update(time);
	}
}

void UnitManager::draw(GraphicsBuffer* gBuff)
{
	for (int i = 0; i < mUnitList.size(); i++)
	{
		mUnitList[i]->draw(gBuff);
	}
}

void UnitManager::addUnit(Method steeringType)
{
	Vector2D pos = mPlayerUnit->getPosition();
	Vector2D vel(0.0f, 0.0f);
	KinematicUnit* newUnit;


	if (steeringType == Arrive)
	{
		pos.setX(pos.getX + 200); // 200p away in x
		newUnit = new KinematicUnit(mpSpriteManager->getSprite(mEnemyID), pos, 1, vel, 0.0f, 180.0f, 100.0f);
		newUnit->dynamicSeek(mPlayerUnit);
		
		// 200p away and arrive 
	}
	else if (steeringType == Seek)
	{
		pos.setX(pos.getX + 100); //100p away in x
		newUnit = new KinematicUnit(mpSpriteManager->getSprite(mEnemyID), pos, 1, vel, 0.0f, 180.0f, 100.0f);
		newUnit->dynamicSeek(mPlayerUnit);
		//100p away and seek
	}
	mUnitList.push_back(newUnit);


}

// not needed until deletion parameters are known
void UnitManager::deleteUnit()
{

}

void UnitManager::deleteRandomUnit()
{
	int index = rand() % (mUnitList.size());

	delete mUnitList[index];
	mUnitList[index] = NULL;
	
	mUnitList.erase(mUnitList.begin() + index);
}


