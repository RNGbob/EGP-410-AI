#pragma once
#include "Game.h"
#include "BoxCollider.h"
#include "Sprite.h"

class Candy :public Trackable
{
public:
	Candy(Sprite *pSprite, const Vector2D position);
	~Candy() {};

	void draw(GraphicsBuffer* pBuffer);
	BoxCollider* getCollider() { return &mBox; }

private:
	BoxCollider mBox;
	Vector2D mPos;
	Sprite* mpSprite;

};