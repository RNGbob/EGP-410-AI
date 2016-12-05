#pragma once

#include <vector>
#include <Trackable.h>
#include "Node.h"

class Node;

class Path:public Trackable
{
public:
	Path();
	~Path();

	Node* peekNode( int index ) const;
	Node* getNode(NODE_ID id) const;
	Node* peekNextNode() const;
	Node* getAndRemoveNextNode();
	bool containsNode( Node* pNode ) const;
	bool isBack(Node* pNode)const;
	bool isEmpty() { return mNodes.empty(); }
	int getNumNodes() const { return mNodes.size(); };
	int getNodeIndex(Node* pNode) const;
	void push_front(Node* node) { mNodes.insert(mNodes.begin(), node); }

	void addNode( Node* pNode );
	void clear();//remove all nodes

	void operator=(Path rhs);

private:
	std::vector<Node*> mNodes;

};