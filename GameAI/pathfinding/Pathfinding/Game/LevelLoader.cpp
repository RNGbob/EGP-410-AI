#include "LevelLoader.h"
#include "GameApp.h"
#include <fstream>

LevelLoader::LevelLoader()
{
	mFiles[0] = "Level1.txt"; 
	mFiles[1] = "Level2.txt"; 
	mFiles[2] = "Level3.txt"; 
	mFiles[3] = "Level4.txt";
}

LevelLoader::~LevelLoader()
{
	while (!mLevels.empty())
	{
		delete mLevels.back();
		mLevels.back() = NULL;
		mLevels.pop_back();
	}
}

void LevelLoader::init()
{
	Level* newLevel;
	Grid* newGrid = new Grid(gpGame->getGraphicsSystem()->getWidth(), gpGame->getGraphicsSystem()->getHeight(), GRID_SQUARE_SIZE);
	
	for (int i = 0; i < 4; ++i)
	{
		newGrid = new Grid(gpGame->getGraphicsSystem()->getWidth(), gpGame->getGraphicsSystem()->getHeight(), GRID_SQUARE_SIZE);
		std::ifstream stream(FILE_PATH + mFiles[i]);
		newGrid->load(stream);
		newLevel = new Level(newGrid);
		mLevels.push_back(newLevel);
		stream.close();
	}
}

void LevelLoader::clear()
{
	
}

Level * LevelLoader::getLevel(int index)
{
	//if (!mLevels.empty() && index < mLevels.size())
	//{
	Level* pLevel =	mLevels[index];
	return pLevel;
	//}
	return nullptr;
}




Level::Level(Grid * pGrid)
:mpGrid(pGrid)
{
	mpVisualizer = new GridVisualizer(mpGrid);
	mpItemManager = new ItemManager();
	mpMapWalls = new MapWallManager();
	mpMapWalls->initWalls(mpGrid);
	
	mpGridGraph = new GridGraph(mpGrid);
	mpGridGraph->init();

	int size = mpGrid->getGridWidth() * mpGrid->getGridHeight();
	
	for (int i = 0; i<size; i++)
	{
		if (mpGrid->getValueAtIndex(i) == 0)
		{
			// not all, make it every 3 or something
			if (i%3 == 0)
			{
				mpItemManager->addCoin(i, mpGrid);
			}
			
		}
		if (mpGrid->getValueAtIndex(i) == 2)
		{
			mpItemManager->addCandy(i, mpGrid);
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

	delete mpGridGraph;
	mpGridGraph = NULL;

	delete mpVisualizer;
	mpVisualizer = NULL;
}

void Level::draw(GraphicsBuffer * pBuffer)
{
	mpVisualizer->draw(*pBuffer);
	mpItemManager->draw(pBuffer);

}
