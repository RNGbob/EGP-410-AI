#pragma once
#include "Game.h"
#include "BoxCollider.h"

class Coin : public Trackable
{
public:
	Coin();
	~Coin();

	void draw();


private:
	BoxCollider mBox;

};