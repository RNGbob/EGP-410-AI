#pragma once

#include "Pathfinder.h"
#include "Node.h"
class GridGraph;
class GridVisualizer;
class GraphicsBuffer;
class PathfindingDebugContent;

class GridPathfinder:public Pathfinder
{
public:
	friend class PathfindingDebugContent;

	GridPathfinder( GridGraph* pGraph );
	virtual ~GridPathfinder();

	virtual const Path& findPath( Node* pFrom, Node* pTo ) = 0;
	virtual const std::string getPathType() = 0;
	void clearPath() { mPath.clear(); }
	
#ifdef VISUALIZE_PATH
	//just for visualization
public:
	void drawVisualization( Grid* pGrid, GraphicsBuffer* pDest );
	void drawLines(NODE_ID node);

protected:
	std::vector<Node*> mVisitedNodes;
	GridVisualizer* mpVisualizer;
#endif
	int lineGetX(NODE_ID node);
	int lineGetY(NODE_ID node);
	double mTimeElapsed;
	std::string mPathType;
};