#pragma once
#include "Game.h"
#include "BoxCollider.h"
#include "Sprite.h"

class Coin : public Trackable
{
public:
	Coin(Sprite *pSprite, const Vector2D position);
	~Coin() {};

	void draw(GraphicsBuffer* pBuffer);
	BoxCollider* getCollider() { return &mBox; }

private:
	BoxCollider mBox;
	Vector2D mPos;
	Sprite* mpSprite;
};