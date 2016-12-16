#pragma once

#include <vector>
#include <deque>
#include <Trackable.h>
#include "Vector2D.h"
#include "Node.h"

class Node;

class Path:public Trackable
{
public:
	Path();
	~Path();

	Node* peekNode( int index ) const;
	Node* getNode(NODE_ID id);//const;
	Node* peekNextNode() const;
	Node* getAndRemoveNextNode();
	bool containsNode( Node* pNode ) const;
	bool isBack(Node* pNode)const;
	bool isEmpty() { return mNodes.empty(); }
	int getNumNodes() const { return mNodes.size(); };
	int getNodeIndex(Node* pNode) const;
	//void push_front(Node* node) { mNodes.push_front(node); }
	int pathSize() { return mNodes.size(); }
	Vector2D startingDirection();

	void addNode( Node* pNode );
	void clear();//remove all nodes

	void operator=(Path rhs);

private:
	std::vector<Node*> mNodes;

};