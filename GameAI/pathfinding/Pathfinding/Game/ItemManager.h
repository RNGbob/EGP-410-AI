#pragma once
#include "Game.h"
#include "Grid.h"
#include "Coin.h"
#include "Candy.h"
#include <vector>

class ItemManager : public Trackable
{
public:
	ItemManager() {};
	~ItemManager();

	void addCoin(int gridIndex, Grid* pGrid);
	void addCandy(int gridIndex,Grid* pGrid);

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