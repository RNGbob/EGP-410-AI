#pragma once
#include "Game.h"
#include "Coin.h"
#include "Candy.h"
#include <vector>

class ItemManager : public Trackable
{
public:
	ItemManager();
	~ItemManager();

	void draw();

	Coin* checkCoins(BoxCollider box);

private:
	std::vector<Coin*> mCoins;
	std::vector<Candy*> mCandies;


};