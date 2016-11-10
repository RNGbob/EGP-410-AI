#pragma once

#include <vector>
#include <Trackable.h>

class Node;

class Path:public Trackable
{
public:
	Path();
	~Path();

	Node* peekNode( int index ) const;
	Node* peekNextNode() const;
	Node* getAndRemoveNextNode();
	bool containsNode( Node* pNode ) const;
	bool isBack(Node* pNode)const;
	int getNumNodes() const { return mNodes.size(); };
	int getNodeIndex(Node* pNode) const;

	void addNode( Node* pNode );
	void clear();//remove all nodes

	void operator=(Path rhs);

private:
	std::vector<Node*> mNodes;

};