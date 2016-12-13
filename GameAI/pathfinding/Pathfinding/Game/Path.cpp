#include "Path.h"

Path::Path()
{
}

Path::~Path()
{
}

Node* Path::peekNode( int index ) const
{
	if( (unsigned int)index < mNodes.size() )
	{
		return mNodes[index];
	}
	else
	{
		return NULL;
	}
}

Node * Path::getNode(NODE_ID id)// const
{
	if (!mNodes.empty()&& id != BAD_NODE_ID)
	{
		for each (Node* node in mNodes)
		{
			if (node->getId() == id)
			{
				return node;
			}
		}
		
		/*
	for (int i = 0; i<mNodes.size(); i++)
	{
		if (mNodes[i]->getId() == id)
		{
			Node* rNode = mNodes[i];
			return rNode;
		}
	}*/
	}
	
	return nullptr;
}

Node* Path::peekNextNode() const
{
	if( mNodes.size() > 0 )
	{
		return mNodes.back();
	}
	else
	{
		return NULL;
	}
}

Node* Path::getAndRemoveNextNode()
{
	if( mNodes.size() > 0 )
	{
		Node* pNode = mNodes.back();
		mNodes.pop_back();
		return pNode;
	}
	else
	{
		return NULL;
	}
}

Vector2D Path::startingDirection()
{
	int indexDiff = mNodes[0]->getId() - mNodes[1]->getId();
	
	if (indexDiff > 0) 
	{
		if (abs(indexDiff)>16)
		{return Vector2D(0,-1);}
		else
		{return Vector2D(-1, 0);}

	}
	else
	{
		if (abs(indexDiff)>16) 
		{return Vector2D(0, 1);}
		else
		{return Vector2D(1, 0);}
	}
	
	
	return Vector2D(0,0);
}

void Path::addNode( Node* pNode )
{
	mNodes.push_back( pNode );
}

bool Path::containsNode( Node* pNode ) const
{
	bool retVal = false;

	for( unsigned int i=0; i<mNodes.size(); i++ )
	{
		if( mNodes[i] == pNode )
		{
			retVal = true;
			break;
		}
	}
	return retVal;
}

bool Path::isBack(Node * pNode) const
{
	bool retVal = false;
	
	if (pNode == mNodes.back())
	{
		retVal = true;
	}
	return retVal;
}

int Path::getNodeIndex(Node* pNode) const
{
	int retVal = -1 ; // if returned used for error checking

	for (unsigned int i = 0; i<mNodes.size(); i++)
	{
		if (mNodes[i] == pNode)
		{
			retVal = i;
			break;
		}
	}
	return retVal;
	
}


void Path::clear()
{
	for (int i = 0; i < mNodes.size(); i++)
	{
		mNodes[i]->setPrevious(BAD_NODE_ID);
	}
	mNodes.clear();
}

void Path::operator=(Path rhs)
{
	mNodes = rhs.mNodes;
}
