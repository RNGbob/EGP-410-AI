#include "PathfindingDebugContent.h"
#include "GameApp.h"
#include "Player.h"
#include "GridPathfinder.h"
#include "Path.h"
#include <sstream>

using namespace std;

PathfindingDebugContent::PathfindingDebugContent( GridPathfinder* pPathfinder )
	:mpPathfinder(pPathfinder)
{
}

string PathfindingDebugContent::getDebugString()
{
	stringstream theStream;
	Player* player = dynamic_cast<Player*>(gpGameA->getPlayerUnit());
/*
#ifdef VISUALIZE_PATH
	theStream << "Pathlength:"<< mpPathfinder->mPath.getNumNodes();
	
	theStream << "   Num Nodes Processed: " << mpPathfinder->mVisitedNodes.size();
#endif
	theStream << "   Elapsed Time: " << mpPathfinder->mTimeElapsed;

	theStream << "   Pathfinding Method: " << mpPathfinder->mPathType;
 */
	theStream << "Score :  " << player->getScore();
	theStream << "   Level :  " << gpGameA->getCurrentLevelIndex() + 1;

	return theStream.str();
}

