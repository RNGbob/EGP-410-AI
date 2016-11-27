#include "Coin.h"


Coin::Coin(Sprite * pSprite, const Vector2D position)
:mpSprite(pSprite),
mPos(position)
{
}

void Coin::draw(GraphicsBuffer * pBuffer)
{
	mpSprite->draw(*pBuffer, mPos.getX(), mPos.getY());
}
