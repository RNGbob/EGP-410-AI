#include "Coin.h"


Coin::Coin(Sprite * pSprite, const Vector2D position)
:mpSprite(pSprite),
mPos(position)
{
	mBox = BoxCollider(mPos, Vector2D(32, 32));
}

Coin::~Coin()
{
}

void Coin::draw(GraphicsBuffer * pBuffer)
{
	mpSprite->draw(*pBuffer, mPos.getX(), mPos.getY());
}
