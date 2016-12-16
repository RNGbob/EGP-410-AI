#include "Candy.h"


Candy::Candy(Sprite * pSprite, const Vector2D position)
:mpSprite(pSprite),
mPos(position)
{
	mBox = BoxCollider(mPos, Vector2D(32, 32));
}

Candy::~Candy()
{
}

void Candy::draw(GraphicsBuffer * pBuffer)
{
	mpSprite->draw(*pBuffer, mPos.getX(), mPos.getY());
}
