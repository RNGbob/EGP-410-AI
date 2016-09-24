#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "AddingMessage.h"


// adding message
AddingMessage::AddingMessage(const Method steeringType)
:GameMessage(ADDING_MESSAGE)
,mType(steeringType)
{
}

AddingMessage::~AddingMessage(){}


void AddingMessage::process()
{
	//gpgame->getUnitManager()->addUnit(mType) // or something like when game.cpp is changed
}



// deleting message
DeletingMessage::DeletingMessage()
:GameMessage(ADDING_MESSAGE)
{
}

DeletingMessage::~DeletingMessage() {}


void DeletingMessage::process()
{
	//gpgame->getUnitManager()->deleteRandomUnit // or something like when game.cpp is changed
}

