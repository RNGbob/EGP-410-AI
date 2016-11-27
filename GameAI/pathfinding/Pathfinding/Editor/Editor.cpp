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
const IDType BACKGROUND_ID = ENDING_SEQUENTIAL_ID + 1;

Editor::Editor()
:Game()
, mpGrid(NULL)
, mpGridVisualizer(NULL)
, mLevelIndex('1')
{
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

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( BACKGROUND_ID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
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
			cout << "Grid saved!\n";
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
			cout << "Grid loaded!\n";
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
			cout << "Grid loaded!\n";
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
			cout << "Grid loaded!\n";
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
			cout << "Grid loaded!\n";
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
			cout << "Grid loaded!\n";
			Sleep(1000);//very bogus
		}
	}
	
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state( &mouseState );

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

	//copy to back buffer
	mpGridVisualizer->draw(*(mpGraphicsSystem->getBackBuffer()));

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
