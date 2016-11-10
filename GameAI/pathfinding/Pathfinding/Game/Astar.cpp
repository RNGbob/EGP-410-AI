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
			pTempPath = Path();
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

				if (heuristic(pCurrentNode,pTempToNode,pTo))
				{
					nodesToVisit.push_front( pTempToNode );
				}
				else
				{
					nodesToVisit.push_back(pTempToNode);
				}

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

bool Astar::heuristic(Node * current, Node* temp, Node* pTo)
{
	bool retVal = false;

	int currentIndex, tempIndex, pToIndex;
	currentIndex = static_cast<int>(current->getId());
	tempIndex = static_cast<int>(temp->getId());
	pToIndex = static_cast<int>(pTo->getId());

	
	if ((getXdiff(currentIndex, pToIndex)>getXdiff(tempIndex, pToIndex))
		|| (getYdiff(currentIndex, pToIndex)>getYdiff(tempIndex, pToIndex)))
	{
		retVal = true;
	}


	return retVal;
}

int Astar::getXdiff(int from, int to)
{
	int fromX = from % 32;
	int toX = to % 32;
	
	int diff = abs(toX - fromX);

	return diff;
}

int Astar::getYdiff(int from, int to)
{
	int fromY = from / 32;
	int toY = to / 32;

	int diff = abs(toY - fromY);

	return diff;
}
