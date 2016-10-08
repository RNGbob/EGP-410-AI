#pragma once
#include "GameMessage.h"
#include "Game.h"

class DebugMessage :public GameMessage
{
public:
	DebugMessage(ChangeableVal val, int mod); // takes enum of steering method for new entity
	~DebugMessage();

	void process();
private:
	ChangeableVal mVal;
	int mMod;


};