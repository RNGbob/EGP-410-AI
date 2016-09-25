#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "AddingMessage.h"
#include "UnitManager.h"


// adding message
AddingMessage::AddingMessage(const Method steeringType)
:GameMessage(ADDING_MESSAGE)
,mType(steeringType)
{
}

AddingMessage::~AddingMessage(){}


void AddingMessage::process()
{
	gpGame->getUnitManager()->addUnit(mType); // or something like when game.cpp is changed
}



// deleting message
DeletingMessage::DeletingMessage()
:GameMessage(ADDING_MESSAGE)
{
}
DeletingMessage::~DeletingMessage() {}


void DeletingMessage::process()
{
	gpGame->getUnitManager()->deleteRandomUnit(); // or something like when game.cpp is changed
}

