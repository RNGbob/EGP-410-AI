#include "UnitManager.h"



UnitManager::UnitManager()
{

}

UnitManager::~UnitManager()
{

}

void UnitManager::init()
{
	// create plater unit
}

void UnitManager::cleanup()
{

}

void UnitManager::addUnit(Method steeringType, Sprite* &sprite)
{
	Vector2D pos(0.0f, 0.0f);
	Vector2D vel(0.0f, 0.0f);


	
	KinematicUnit* newUnit = new KinematicUnit(sprite, pos, 1, vel, 0.0f, 180.0f, 100.0f);



}

/*/
//setup units
Vector2D pos( 0.0f, 0.0f );
Vector2D vel( 0.0f, 0.0f );
mpUnit = new KinematicUnit( pArrowSprite, pos, 1, vel, 0.0f, 200.0f, 10.0f );

Vector2D pos2( 1000.0f, 500.0f );
Vector2D vel2( 0.0f, 0.0f );
mpAIUnit = new KinematicUnit( pEnemyArrow, pos2, 1, vel2, 0.0f, 180.0f, 100.0f );
//give steering behavior
mpAIUnit->dynamicArrive( mpUnit );

Vector2D pos3( 500.0f, 500.0f );
mpAIUnit2 = new KinematicUnit( pEnemyArrow, pos3, 1, vel2, 0.0f, 180.0f, 100.0f );
//give steering behavior
mpAIUnit2->dynamicSeek( mpUnit );

return true;
/**/



void UnitManager::deleteUnit()
{

}

void UnitManager::deleteRandomUnit()
{

}

/*/
//delete units
delete mpUnit;
mpUnit = NULL;
delete mpAIUnit;
mpAIUnit = NULL;
delete mpAIUnit2;
mpAIUnit2 = NULL;
/**/
