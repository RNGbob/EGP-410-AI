#include "SwitchPathFindingMessage.h"

SwitchPathFindingMessage::SwitchPathFindingMessage(PathfindingType type)
:GameMessage(PATH_TO_MESSAGE)
,mType(type)
{
}

SwitchPathFindingMessage::~SwitchPathFindingMessage()
{
}

void SwitchPathFindingMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);

	switch (mType)
	{
	case DepthBreadthSearch:
		pGame->setDepthBreadth();
		break;
	case DijkstraPath:
		pGame->setDijkstra();
		break;
	case AstarPath:
		pGame->setAstar();
		break;
	default:
		break;
	}

}
