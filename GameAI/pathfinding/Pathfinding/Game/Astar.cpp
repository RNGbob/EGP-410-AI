#include "Astar.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include "GameApp.h"
#include "Grid.h"
#include <PerformanceTracker.h>
#include "LevelLoader.h"
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


	int currentPathIndex;
	float priorityMin = 2;
	float connectWeight;

#ifdef VISUALIZE_PATH
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	mPath.clear();
	mBest.clear();

	Node* pCurrentNode = NULL; 
	pCurrentNode = nodesToVisit.front();
	bool toNodeAdded = false;

	while (pCurrentNode != pTo && nodesToVisit.size() > 0)
	{

		//get current node from front of list
		pCurrentNode = nodesToVisit.front();
		//remove node from list
		nodesToVisit.pop_front();
		//add Node to Path
		mPath.addNode(pCurrentNode);

		

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
				
				// pushes front if meets heuristic criteria
				if (!heuristic(pCurrentNode,pTempToNode,pTo))
				{
					connectWeight += 1;
				}

				
				if (connectWeight < priorityMin) // will be true if with heuristic
				{
					nodesToVisit.push_front( pTempToNode );
				}
				else
				{
					nodesToVisit.push_back(pTempToNode);
				}

				if (pTempToNode == pTo)
				{
					toNodeAdded = true;
				}

#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(pTempToNode);
#endif

			}
		}
		//pathsMade.erase(pathsMade.begin() + currentPathIndex);
	}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	bestPath();
	//Path best;
	
	if (!mBest.isEmpty())
	{
		return mBest;
	}

	return mPath;
}
void Astar::bestPath()
{
	if (!mPath.isEmpty())
	{
		std::vector<Node*> reverse;
		Node* prevNode = mPath.peekNextNode();
		NODE_ID id = BAD_NODE_ID;
		/**/
		while (prevNode != nullptr && prevNode !=NULL)
		{
			reverse.push_back(prevNode);
			//bestPath.push_front(prevNode);
			id = prevNode->getPrev();
			prevNode = mPath.getNode(id);

		}
		while (!reverse.empty())
		{
			mBest.addNode(reverse.back());
			reverse.pop_back();
		}
	}
	
}
// psuedo manhattan distance, returns true if closer x or y
bool Astar::heuristic(Node * current, Node* temp, Node* pTo)
{
	bool retVal = false;

	int currentIndex, tempIndex, pToIndex;
	currentIndex = static_cast<int>(current->getId());
	tempIndex = static_cast<int>(temp->getId());
	pToIndex = static_cast<int>(pTo->getId());

	// true if the difference between x or y axis decreases from current node to previous node.
	if ((getXdiff(currentIndex, pToIndex) > getXdiff(tempIndex, pToIndex)) // is tempNode difference less in x?
		|| (getYdiff(currentIndex, pToIndex)>getYdiff(tempIndex, pToIndex))) // is tempNode difference less in y?
	{
		retVal = true;
	}


	return retVal;
}

int Astar::getXdiff(int from, int to)
{
	//GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	
	int fromX = from % gpGameA->getLevel()->getGrid()->getSquareSize();
	int toX = to % gpGameA->getLevel()->getGrid()->getSquareSize();
	
	int diff = abs(toX - fromX);

	return diff; // absolute difference of x indices 
}

int Astar::getYdiff(int from, int to)
{
	//GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	
	int fromY = from / gpGameA->getLevel()->getGrid()->getSquareSize();
	int toY = to / gpGameA->getLevel()->getGrid()->getSquareSize();

	int diff = abs(toY - fromY);  //absolute difference of x indices

	return diff;
}
