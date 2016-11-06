#include "Astar.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

Astar::Astar(Graph * pGraph)
:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
	mPathType = "A* ";
}

Astar::~Astar()
{
}

const Path & Astar::findPath(Node * pFrom, Node * pTo)
{
	// Soon.....
	return mPath;
}
