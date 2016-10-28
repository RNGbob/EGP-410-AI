#include "CircleCollider.h"
#include "BoxCollider.h"

CircleCollider::CircleCollider()
{
}

CircleCollider::CircleCollider(Vector2D pos, float radius)
:mPos(pos)
,mRadius(radius)
{
}

CircleCollider::~CircleCollider()
{
}

bool CircleCollider::checkCollison(BoxCollider *& other)
{
	if (mPos.getX() - mRadius > (other->getPos().getX() + other->getDim().getX()) ||
		mPos.getY() - mRadius > (other->getPos().getY() + other->getDim().getY()) ||
		other->getPos().getX() > mPos.getX() + mRadius   ||
		other->getPos().getY() > mPos.getY() + mRadius  )
	{
		return false;
	}
	else { return true; }
	
}

bool CircleCollider::checkCollison(CircleCollider *& other)
{
	Vector2D distanceVec = mPos - other->getPos();
	float distance = distanceVec.getLength();
	
	if (distance < (mRadius +other->getRadius()))
	{
		return true;
	}
	
	return false;
}
