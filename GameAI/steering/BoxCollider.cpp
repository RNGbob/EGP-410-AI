#include "BoxCollider.h"
#include "CircleCollider.h"

BoxCollider::BoxCollider()
{
}


BoxCollider::BoxCollider(Vector2D pos, Vector2D dim)
:mPos(pos),
mDim(dim)
{
}

BoxCollider::~BoxCollider()
{
}

bool BoxCollider::checkCollison(BoxCollider* &other)
{
	if (other->getPos().getX() > (mPos.getX() + mDim.getX()) ||
		other->getPos().getY() > (mPos.getY() + mDim.getY()) ||
		mPos.getX() > (other->getPos().getX() + other->getDim().getX()) ||
		mPos.getY() > (other->getPos().getY() + other->getDim().getY())
		)
	{
		return false;
	}
	else { return true; }


}

bool BoxCollider::checkCollison(CircleCollider *& other)
{
	if (other->getPos().getX() - other->getRadius() > (mPos.getX() + mDim.getX()) ||
		other->getPos().getY() - other->getRadius() > (mPos.getY() + mDim.getY()) ||
		mPos.getX() > (other->getPos().getX() + other->getRadius()) ||
		mPos.getY() > (other->getPos().getY() + other->getRadius())
		)
	{
		return false;
	}
	else { return true; }
	
}
