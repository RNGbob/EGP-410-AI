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
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it
	std::list<Node*> nodesToVisit;
	nodesToVisit.push_front(pFrom);

	std::vector<Path> pathsMade;
	Path pTempPath;
	int currentPathIndex;

#ifdef VISUALIZE_PATH
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	mPath.clear();

	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;

	while (pCurrentNode != pTo && nodesToVisit.size() > 0)
	{
		
		//get current node from front of list
		pCurrentNode = nodesToVisit.front();
		//remove node from list
		nodesToVisit.pop_front();
		//add Node to Path
		mPath.addNode(pCurrentNode);

		if (pathsMade.empty())
		{
			pTempPath =  Path();
			pTempPath.addNode(pCurrentNode);
			pathsMade.push_back(pTempPath);
			currentPathIndex = 0;
		}
		else
		{
			for (int i = 0; i < pathsMade.size(); ++i)
			{
				if (pathsMade[i].isBack(pCurrentNode))
				{
					currentPathIndex = i;
					break;
				}
			}
		}

		//get the Connections for the current node
		std::vector<Connection*> connections = mpGraph->getConnections(pCurrentNode->getId());

		//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
		for (unsigned int i = 0; i<connections.size(); i++)
		{
			Connection* pConnection = connections[i];
			Node* pTempToNode = connections[i]->getToNode();
			if (!toNodeAdded &&
				!mPath.containsNode(pTempToNode) &&
				find(nodesToVisit.begin(), nodesToVisit.end(), pTempToNode) == nodesToVisit.end())
			{
				
				// breadth first works since all connections have equal weight
				nodesToVisit.push_back(pTempToNode);//uncomment me for breadth-first search
				
				pTempPath = Path();
				pTempPath = pathsMade[currentPathIndex];
				pTempPath.addNode(pTempToNode);
				
				if (pTempToNode == pTo)
				{
					toNodeAdded = true;
				}

				pathsMade.push_back(pTempPath);

#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(pTempToNode);
#endif

			}
		}
		//pathsMade.erase(pathsMade.begin() + currentPathIndex);
	}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	for (int i = 0; i < pathsMade.size(); i++)
	{
		if (pathsMade[i].isBack(pTo))
		{
			mPath = pathsMade[i];
		}
	}

	return mPath;
}
