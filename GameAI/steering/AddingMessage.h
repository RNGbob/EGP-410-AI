#pragma once
#include "GameMessage.h"
//#include "Game.h"


class AddingMessage : public GameMessage
{
public:
	AddingMessage(const Method steeringType); // takes enum of steering method for new entity
	~AddingMessage();

	void process();
private:
	Method mType;
};

// not worthing making own set of files 
class DeletingMessage : public GameMessage
{
public:
	DeletingMessage();
	~DeletingMessage();

	void process();
private:
};