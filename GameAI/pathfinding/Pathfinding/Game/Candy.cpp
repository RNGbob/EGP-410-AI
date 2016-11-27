#include "Candy.h"

Candy::Candy(Sprite * pSprite, const Vector2D position)
:mpSprite(pSprite),
mPos(position)
{
}

void Candy::draw(GraphicsBuffer * pBuffer)
{
	mpSprite->draw(*pBuffer, mPos.getX(), mPos.getY());
}
