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
		mLevels[i]->setIndex(i);
	}
}

void LevelLoader::clear()
{
	
}

void LevelLoader::reload()
{
	mLevels[0]->reload();
	mLevels[1]->reload();
	mLevels[2]->reload();
	mLevels[3]->reload();

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
			if (i%7 == 0)
			{
				mpItemManager->addCoin(i, mpGrid);
			}
			
		}
		if (mpGrid->getValueAtIndex(i) == 2)
		{
			mpItemManager->addCandy(i, mpGrid);
		}
		if (mpGrid->getValueAtIndex(i) == 3)
		{
			mPlayerSpawn = mpGrid->getULCornerOfSquare(i) + Vector2D(2, 2);
		}
		if (mpGrid->getValueAtIndex(i) == 4)
		{
			mEnemySpawn = mpGrid->getULCornerOfSquare(i) + Vector2D(2, 2);
		}

	}
	mpPathfinder = new Astar(mpGridGraph);// will always be A*


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

	delete mpPathfinder;
	mpPathfinder = NULL;
}

void Level::reload()
{
	mpItemManager->clear();

	int size = mpGrid->getGridWidth() * mpGrid->getGridHeight();

	for (int i = 0; i<size; i++)
	{
		if (mpGrid->getValueAtIndex(i) == 0)
		{
			// not all, make it every 3 or something
			if (i % 7 == 0)
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

void Level::draw(GraphicsBuffer * pBuffer)
{
	mpVisualizer->draw(*pBuffer);
	mpItemManager->draw(pBuffer);

}

const Path& Level::findPath(Vector2D from, Vector2D to )
{
	//GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	int fromIndex  = mpGrid->getSquareIndexFromPixelXY((int)from.getX(), (int)from.getY());
	int toIndex;
	if (to == Vector2D(-1,-1))// if player is in different map
	{
		toIndex = getExitIndex(gpGameA->getCurrentLevelIndex());
	}
	else
	{
		toIndex = mpGrid->getSquareIndexFromPixelXY((int)to.getX(), (int)to.getY());
	}
	
	if (toIndex == -1)
	{
		return Path();
	}
	
	
	Node* pFromNode = mpGridGraph->getNode(fromIndex);
	Node* pToNode = mpGridGraph->getNode(toIndex);
	
	return mpPathfinder->findPath(pFromNode,pToNode);
}

int Level::getExitIndex(int cLevel)
{
	if ((mIndex == 0 && cLevel == 1) || (mIndex == 2 && cLevel == 3))
	{
		return 415;// right gate node
	}
	else if ((mIndex == 1 && cLevel == 0) || (mIndex == 3 && cLevel == 2))
	{
		return 385; //left gate node
	}
	else if ((mIndex == 0 && cLevel == 2) || (mIndex == 1 && cLevel == 3))
	{
		return 752;// bottom gate node
	}
	else if ((mIndex == 2 && cLevel == 0) || (mIndex == 3 && cLevel == 1))
	{
		return 16; //top gate node
	}
	
	return -1; //diagonal  difference in maps
}
