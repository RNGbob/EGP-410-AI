#include "UnitManager.h"
#include "KinematicUnit.h"
#include "SpriteManager.h"


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

void UnitManager::init(  SpriteManager* &mpSprMan)
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

void UnitManager::addUnit(Method steeringType)
{
	double theta = rand() % 360;//2*PI;
	
	Vector2D pos(mPlayerUnit->getPosition().getX() + (200 * sin(theta)), mPlayerUnit->getPosition().getY() + (200 * cos(theta))); 
	

	Vector2D vel(0.0f, 0.0f);
	KinematicUnit* newUnit;

	switch (steeringType)
	{
	case WanderSeek:
		newUnit = new KinematicUnit(mpSpriteManager->getSprite(AI_ICON_SPRITE_ID), pos, 1, vel, 0.0f, gpGame->getValue(EnemyVel), gpGame->getValue(AngularVel));
		newUnit->wanderSeek(mPlayerUnit);
		break;
	case WanderFlee:
		newUnit = new KinematicUnit(mpSpriteManager->getSprite(AI_ICON_SPRITE_ID), pos, 1, vel, 0.0f, gpGame->getValue(EnemyVel), gpGame->getValue(AngularVel));
		newUnit->wanderFlee(mPlayerUnit);
		break;
	default:
		break;
	}
	
	/*
	if (steeringType == Arrive)
	{
		pos.setX(pos.getX() + 200); // 200p away in x
		newUnit = new KinematicUnit(mpSpriteManager->getSprite(AI_ICON_SPRITE_ID), pos, 1, vel, 0.0f, gpGame->getValue(EnemyVel), gpGame->getValue(AngularVel));
		newUnit->dynamicArrive(mPlayerUnit);
		
		// 200p away and arrive 
	}
	else if (steeringType == Seek)
	{
		pos.setX(pos.getX() + 100); //100p away in x
		newUnit = new KinematicUnit(mpSpriteManager->getSprite(AI_ICON_SPRITE_ID), pos, 1, vel, 0.0f, gpGame->getValue(EnemyVel), gpGame->getValue(AngularVel));
		newUnit->dynamicSeek(mPlayerUnit);
		//100p away and seek
	}*/

	mUnitList.push_back(newUnit);


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


