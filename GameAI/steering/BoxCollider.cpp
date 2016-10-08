#include "BoxCollider.h"

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

bool BoxCollider::checkBoxCollison(BoxCollider* &other)
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
