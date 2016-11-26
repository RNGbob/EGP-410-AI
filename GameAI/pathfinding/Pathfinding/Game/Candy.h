#pragma once
#include "Game.h"
#include "BoxCollider.h"

class Candy :public Trackable
{
public:
	Candy();
	~Candy();

	void draw();


private:
	BoxCollider mBox;

};