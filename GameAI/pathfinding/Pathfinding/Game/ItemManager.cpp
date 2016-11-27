#include "ItemManager.h"
#include "GameApp.h"
#include "SpriteManager.h"
#include "Grid.h"

void ItemManager::addCoin(int gridIndex)
{
	//GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	//Coin* newCoin = new Coin(pGame->getSpriteManager()->getSprite(SOME_ID), pGame->getGrid()->getULCornerOfSquare(gridIndex));
	//mCoins.push_back(newCoin);
}

void ItemManager::addCandy(int gridIndex)
{
	//GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	//Candy* newCandy = new Candy(pGame->getSpriteManager()->getSprite(SOME_ID), pGame->getGrid()->getULCornerOfSquare(gridIndex));
	//mCandies.push_back(newCandy);
}

void ItemManager::clear()
{
	while (!mCandies.empty())
	{
		delete mCandies.back();
		mCandies.back() = NULL;
		mCandies.pop_back();
	}
	mCandies.clear();
	while (!mCoins.empty())
	{
		delete mCoins.back();
		mCoins.back() = NULL;
		mCoins.pop_back();
	}
	mCoins.clear();
}

void ItemManager::draw(GraphicsBuffer * pBuffer)
{
	for (int i = 0; i < mCoins.size(); ++i)
	{
		mCoins[i]->draw(pBuffer);
	}
	for (int i = 0; i < mCandies.size(); ++i)
	{
		mCandies[i]->draw(pBuffer);
	}

}

Coin * ItemManager::checkCoins(BoxCollider* box)
{
	for (int i = 0; i < mCoins.size(); ++i)
	{
		if (mCoins[i]->getCollider()->checkCollison(box))
		{
			return mCoins[i];
		}
	}
	return nullptr;
}

void ItemManager::removeCoin(Coin* coin)
{
	int index;
	for (int i = 0; i < mCoins.size(); ++i)
	{
		if (mCoins[i] == coin)
		{
			index = i;
			break;
		}
	}
	mCoins.erase(mCoins.begin() + index);

}

Candy * ItemManager::checkCandy(BoxCollider* box)
{
	for (int i = 0; i < mCandies.size(); ++i)
	{
		if (mCandies[i]->getCollider()->checkCollison(box))
		{
			return mCandies[i];
		}
	}
	
	return nullptr;
}

void ItemManager::removeCandy(Candy * candy)
{
	int index;
	for (int i = 0; i < mCandies.size(); ++i)
	{
		if (mCandies[i] == candy)
		{
			index = i;
			break;
		}
	}
	mCandies.erase(mCandies.begin() + index);
}
