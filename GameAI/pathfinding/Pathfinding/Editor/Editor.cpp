#include <fstream>
#include <allegro5/allegro_primitives.h>

#include "Game.h"
#include "Editor.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Grid.h"
#include "GridVisualizer.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Vector2D.h"

using namespace std;

const int GRID_SQUARE_SIZE = 32;
const IDType BACKGROUND_ID =1;
const IDType PLAYER_ID = 2;
const IDType CANDY_ID = 3;
const IDType ENEMY_ID = 4;

Editor::Editor()
:Game()
, mpGrid(NULL)
, mpGridVisualizer(NULL)
, mLevelIndex('1')
{
	PlayerIndex = -1;
	EnemyIndex = -1;
}

Editor::~Editor()
{
	cleanup();
}

bool Editor::init()
{
	bool retVal = Game::init();
	if( retVal == false )
	{

		return false;
	}

	mpGrid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);

	mpGridVisualizer = new GridVisualizer( mpGrid );

	//load buffers
	mpGraphicsBufferManager->loadBuffer( BACKGROUND_ID, FILE_PATH+"wallpaper.bmp");
	mpGraphicsBufferManager->loadBuffer(PLAYER_ID, FILE_PATH + "Player.png");
	mpGraphicsBufferManager->loadBuffer(CANDY_ID, FILE_PATH + "Candy.png");
	mpGraphicsBufferManager->loadBuffer(ENEMY_ID, FILE_PATH + "EnemyGreen.png");
	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( BACKGROUND_ID );
	GraphicsBuffer* pPlayerBuffer = mpGraphicsBufferManager->getBuffer(PLAYER_ID);
	GraphicsBuffer* pCandyBuffer = mpGraphicsBufferManager->getBuffer(CANDY_ID);
	GraphicsBuffer* pEnemyBuffer = mpGraphicsBufferManager->getBuffer(ENEMY_ID);

	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
	}
	if (pPlayerBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(PLAYER_ID, pPlayerBuffer, 0, 0, pPlayerBuffer->getWidth(), pPlayerBuffer->getHeight());
	}
	if (pEnemyBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(ENEMY_ID, pEnemyBuffer, 0, 0, pEnemyBuffer->getWidth(), pEnemyBuffer->getHeight());
	}
	if (pCandyBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(CANDY_ID, pCandyBuffer, 0, 0, pCandyBuffer->getWidth(), pCandyBuffer->getHeight());
	}
	
	mpMasterTimer->start();
	return true;
}

void Editor::cleanup()
{
	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpGrid;
	mpGrid = NULL;
}

void Editor::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void Editor::processLoop()
{
	ALLEGRO_KEYBOARD_STATE keyState;
	al_get_keyboard_state(&keyState);

	//if escape key was down then exit the loop
	if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
	{
		gpGame->markForExit();
	}
	else if (al_key_down(&keyState, ALLEGRO_KEY_S))
	{
		Editor* pEditor = dynamic_cast<Editor*>(gpGame);
		if (pEditor != NULL)
		{
			string file = FILE_NAME + mLevelIndex + ".txt";
			ofstream theStream(file);
			pEditor->saveGrid(theStream);
			theStream.close();
			cout << "Grid " << mLevelIndex << " saved!\n";
			Sleep(1000);//very bogus
		}
	}
	else if (al_key_down(&keyState, ALLEGRO_KEY_L))
	{
		Editor* pEditor = dynamic_cast<Editor*>(gpGame);
		if (pEditor != NULL)
		{
			string file = FILE_NAME + mLevelIndex + ".txt";
			ifstream theStream(file);
			pEditor->loadGrid(theStream);
			theStream.close();
			pEditor->getGridVisualizer()->setModified();
			cout << "Grid " << mLevelIndex << " loaded!\n";
			Sleep(1000);//very bogus
		}
	}
	else if (al_key_down(&keyState, ALLEGRO_KEY_C))
	{
		clearGrid();
	}
	else if (al_key_down(&keyState, ALLEGRO_KEY_1))
	{
		mLevelIndex = '1';
		Editor* pEditor = dynamic_cast<Editor*>(gpGame);
		if (pEditor != NULL)
		{
			string file = FILE_NAME + mLevelIndex + ".txt";
			ifstream theStream(file);
			pEditor->loadGrid(theStream);
			theStream.close();
			pEditor->getGridVisualizer()->setModified();
			cout << "Grid " << mLevelIndex << " loaded!\n";
			Sleep(1000);//very bogus
		}
	}
	else if (al_key_down(&keyState, ALLEGRO_KEY_2))
	{
		mLevelIndex = '2';
		Editor* pEditor = dynamic_cast<Editor*>(gpGame);
		if (pEditor != NULL)
		{
			string file = FILE_NAME + mLevelIndex + ".txt";
			ifstream theStream(file);
			pEditor->loadGrid(theStream);
			theStream.close();
			pEditor->getGridVisualizer()->setModified();
			cout << "Grid " << mLevelIndex << " loaded!\n";
			Sleep(1000);//very bogus
		}
	}
	else if (al_key_down(&keyState, ALLEGRO_KEY_3))
	{
		mLevelIndex = '3';
		Editor* pEditor = dynamic_cast<Editor*>(gpGame);
		if (pEditor != NULL)
		{
			string file = FILE_NAME + mLevelIndex + ".txt";
			ifstream theStream(file);
			pEditor->loadGrid(theStream);
			theStream.close();
			pEditor->getGridVisualizer()->setModified();
			cout << "Grid " << mLevelIndex << " loaded!\n";
			Sleep(1000);//very bogus
		}
	}
	else if (al_key_down(&keyState, ALLEGRO_KEY_4))
	{
		mLevelIndex = '4';
		Editor* pEditor = dynamic_cast<Editor*>(gpGame);
		if (pEditor != NULL)
		{
			string file = FILE_NAME + mLevelIndex + ".txt";
			ifstream theStream(file);
			pEditor->loadGrid(theStream);
			theStream.close();
			pEditor->getGridVisualizer()->setModified();
			cout << "Grid " << mLevelIndex << " loaded!\n";
			Sleep(1000);//very bogus
		}
	}
	
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state( &mouseState );

	if (shift(keyState))
	{
		if (firstPress(mouseState,prevKey,1))//al_mouse_button_down(&mouseState, 1))
		{
			mpGrid->setValueAtPixelXY(mouseState.x, mouseState.y, PLAYER_SPAWN_VALUE);
			mpGridVisualizer->setModified();
			mpGrid->setValueAtIndex(PlayerIndex, CLEAR_VALUE);   
			PlayerIndex = mpGrid->getSquareIndexFromPixelXY(mouseState.x, mouseState.y);
		}
		else if (firstPress(mouseState, prevKey, 2))
		{
			mpGrid->setValueAtPixelXY(mouseState.x, mouseState.y, ENEMY_SPAWN_VALUE);
			mpGridVisualizer->setModified();
			mpGrid->setValueAtIndex(EnemyIndex, CLEAR_VALUE);
			EnemyIndex = mpGrid->getSquareIndexFromPixelXY(mouseState.x, mouseState.y);
		}
		else if (al_mouse_button_down(&mouseState, 3))
		{
			mpGrid->setValueAtPixelXY(mouseState.x, mouseState.y, POWER_UP_VALUE);
			mpGridVisualizer->setModified();
			//mSpritePos.push_back(mpGrid->getULCornerOfSquare(mpGrid->getSquareIndexFromPixelXY(mouseState.x, mouseState.y)));
		}
	}
	else
	{
		if( al_mouse_button_down( &mouseState, 1 ) )//left mouse click
		{
			mpGrid->setValueAtPixelXY( mouseState.x, mouseState.y, BLOCKING_VALUE );
			mpGridVisualizer->setModified();
		}
		else if( al_mouse_button_down( &mouseState, 2 ) )//right mouse down
		{
			mpGrid->setValueAtPixelXY( mouseState.x, mouseState.y, CLEAR_VALUE );
			mpGridVisualizer->setModified();
		}
	}
	
	prevKey = mouseState;
	//copy to back buffer
	mpGridVisualizer->draw(*(mpGraphicsSystem->getBackBuffer()));
	draw();
	//should be last thing in processLoop
	Game::processLoop();
}

bool Editor::endLoop()
{
	return Game::endLoop();
}

void Editor::saveGrid( ofstream& theStream )
{
	mpGrid->save( theStream );
}

void Editor::loadGrid( std::ifstream& theStream )
{
	mpGrid->load(theStream);
	
	int size = mpGrid->getGridWidth() * mpGrid->getGridHeight();
	//get any non-zero squares and send them to the visualizer
	for (int i = 0; i<size; i++)
	{
		if (mpGrid->getValueAtIndex(i) == 3)
		{
			PlayerIndex = i; 
		}
		if (mpGrid->getValueAtIndex(i) == 4)
		{
			EnemyIndex = i;
		}
	}
	


}

void Editor::clearGrid()
{
	Editor* pEditor = dynamic_cast<Editor*>(gpGame);
	if (pEditor != NULL)
	{
		ifstream theStream(FILE_PATH + "Blank.txt");
		mpGrid->load(theStream);
		theStream.close();
		pEditor->getGridVisualizer()->setModified();
	}
}

void Editor::setPlayerSpawn()
{
}

void Editor::setEnemySpawn()
{
}

void Editor::draw()
{
	int size = mpGrid->getGridWidth() * mpGrid->getGridHeight();
	//get any non-zero squares and send them to the visualizer
	for (int i = 0; i<size; i++)
	{
		if (mpGrid->getValueAtIndex(i) == 2)
		{
			mpSpriteManager->getSprite(CANDY_ID)->draw(*(mpGraphicsSystem->getBackBuffer()), mpGrid->getULCornerOfSquare(i).getX(), mpGrid->getULCornerOfSquare(i).getY());
		}
		if (mpGrid->getValueAtIndex(i) == 3)
		{
			mpSpriteManager->getSprite(PLAYER_ID)->draw(*(mpGraphicsSystem->getBackBuffer()), mpGrid->getULCornerOfSquare(i).getX(), mpGrid->getULCornerOfSquare(i).getY());
		}
		if (mpGrid->getValueAtIndex(i) == 4)
		{
			mpSpriteManager->getSprite(ENEMY_ID)->draw(*(mpGraphicsSystem->getBackBuffer()), mpGrid->getULCornerOfSquare(i).getX(), mpGrid->getULCornerOfSquare(i).getY());
		}
	}
	


}

bool Editor::shift(ALLEGRO_KEYBOARD_STATE keyState)
{
	if (al_key_down(&keyState, ALLEGRO_KEY_RSHIFT) || al_key_down(&keyState, ALLEGRO_KEY_LSHIFT))
	{
		return true;
	}
	
	return false;
}

bool Editor::firstPress(ALLEGRO_MOUSE_STATE& now, ALLEGRO_MOUSE_STATE& last, int mouseButton)
{
	return ((al_mouse_button_down(&now, mouseButton)) && !(al_mouse_button_down(&last, mouseButton)));
}
