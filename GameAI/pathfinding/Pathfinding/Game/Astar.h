#pragma once

#include "GridPathfinder.h"
#include <vector>


class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class Astar :public GridPathfinder
{
public:
	Astar(Graph* pGraph);
	~Astar();

	const Path& findPath(Node* pFrom, Node* pTo);
	const std::string getPathType() { return "A*"; }
	void bestPath(Path &best);

	bool heuristic(Node* current, Node* temp, Node* pTo);
	int getXdiff(int from, int to);
	int getYdiff(int from, int to);

private:
};
