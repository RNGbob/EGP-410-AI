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

	int currentPathIndex;
	float priorityMin = 1;
	float connectWeight;

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

		// initialize base path on first run
		

		//get the Connections for the current node
		std::vector<Connection*> connections = mpGraph->getConnections(pCurrentNode->getId());

		//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
		for (unsigned int i = 0; i<connections.size(); i++)
		{
			Connection* pConnection = connections[i];
			connectWeight = pConnection->getCost();
			Node* pTempToNode = connections[i]->getToNode();
			if (!toNodeAdded &&
				!mPath.containsNode(pTempToNode) &&
				find(nodesToVisit.begin(), nodesToVisit.end(), pTempToNode) == nodesToVisit.end())
			{
				pTempToNode->setPrevious(pCurrentNode->getId());

				// breadth first works since all connections have equal weight
				// with gridgraphs weight calculations are not necessary making path length = to weight of traversal
				// wont actually push front for grid dijkstra
				if (connectWeight < priorityMin)
				{
					nodesToVisit.push_front(pTempToNode);
				}
				else
				{
					nodesToVisit.push_back(pTempToNode);
				}
				
				
				//nodesToVisit.push_back(pTempToNode);//uncomment me for breadth-first search
				
			
				if (pTempToNode == pTo)
				{
					toNodeAdded = true;
				}
				

#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(pTempToNode);
#endif

			}
		}
		
	}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");


	return mPath;
}
