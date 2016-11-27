#include "LevelLoader.h"
#include <fstream>

LevelLoader::LevelLoader()
{
	mFiles[0] = "Level1.txt"; 
	mFiles[1] = "Level2.txt"; 
	mFiles[2] = "Level3.txt"; 
	mFiles[3] = "Level4.txt";
}

void LevelLoader::init()
{
	Level* newLevel;
	Grid* newGrid;
	
	for (int i = 0; i < 4; ++i)
	{
		std::ifstream stream(mFiles[i]);
		newGrid->load(stream);
		newLevel = new Level(newGrid);
		mLevels.push_back(newLevel);
		stream.close();
	}
}

void LevelLoader::clear()
{
	while (!mLevels.empty())
	{
		delete mLevels.back();
		mLevels.back = NULL;
		mLevels.pop_back();
	}
}

Level * LevelLoader::getLevel(int index)
{
	if (!mLevels.empty() && index < mLevels.size())
	{
		return mLevels[index];
	}
	return nullptr;
}




Level::Level(Grid * pGrid)
:mpGrid(pGrid)
{
	mpItemManager = new ItemManager();
	mpMapWalls = new MapWallManager();
	mpMapWalls->initWalls(mpGrid);

	int size = mpGrid->getGridWidth() * mpGrid->getGridHeight();
	
	for (int i = 0; i<size; ++i)
	{
		if (mpGrid->getValueAtIndex(i) == 0)
		{
			// not all, make it every 3 or something
			mpItemManager->addCoin(i);
		}
		if (mpGrid->getValueAtIndex(i) == 2)
		{
			mpItemManager->addCandy(i);
		}

	}

}

Level::~Level()
{
	delete mpGrid;
	mpGrid= NULL;

	delete mpItemManager;
	mpItemManager = NULL;

	delete mpMapWalls;
	mpMapWalls = NULL;


}

void Level::draw(GraphicsBuffer * pBuffer)
{
	mpItemManager->draw(pBuffer);

}
