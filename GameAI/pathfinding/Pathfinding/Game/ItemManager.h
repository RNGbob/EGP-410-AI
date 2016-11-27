#pragma once
#include "Game.h"
#include "Coin.h"
#include "Candy.h"
#include <vector>

class ItemManager : public Trackable
{
public:
	ItemManager() {};
	~ItemManager() { clear(); };

	void addCoin(int gridIndex);
	void addCandy(int gridIndex);

	void clear();

	void draw(GraphicsBuffer* pBuffer);

	Coin* checkCoins(BoxCollider* box);// returns coin collided with
	void removeCoin(Coin* coin);

	Candy* checkCandy(BoxCollider* box);// returns coin collided with
	void removeCandy(Candy* candy);

private:
	std::vector<Coin*> mCoins;
	std::vector<Candy*> mCandies;


};