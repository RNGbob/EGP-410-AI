#pragma once
#include "GameMessage.h"

#include "Vector2D.h"

class PlayerMoveMessage :public GameMessage
{
public:
	PlayerMoveMessage(const Vector2D& direction);
	~PlayerMoveMessage() {};

	void process();

private:
	Vector2D mDirection;
};