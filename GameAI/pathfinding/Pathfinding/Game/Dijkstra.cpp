#include "Dijkstra.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

Dijkstra::Dijkstra(Graph * pGraph)
:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
	mPathType = "Dijkstra";
}

Dijkstra::~Dijkstra()
{
}

const Path & Dijkstra::findPath(Node * pFrom, Node * pTo)
{
	//stuff here eventually
	return mPath;
}
