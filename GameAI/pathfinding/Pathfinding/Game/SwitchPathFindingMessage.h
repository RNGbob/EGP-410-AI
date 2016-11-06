#pragma once
#include "GameMessage.h"
#include "GameApp.h"


class SwitchPathFindingMessage : public GameMessage
{
public:
	SwitchPathFindingMessage(PathfindingType type);
	~SwitchPathFindingMessage();

	void process();

private:
	PathfindingType mType;

};