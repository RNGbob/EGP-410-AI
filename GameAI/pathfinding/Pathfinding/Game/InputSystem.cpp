#include "InputSystem.h"
#include "Game.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "SwitchPathFindingMessage.h"
#include "Grid.h"
#include <string>
#include <sstream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>


InputSystem::InputSystem()
{
	mpMessageManager = nullptr;
}
InputSystem::~InputSystem() {}

void InputSystem::init(GameMessageManager* &mesman)
{
	mpMessageManager = mesman;
	firstSelect = false;
}

void InputSystem::cleanup()// easier to call rather than depending on destructor call;
{
	delete mpMessageManager;
	mpMessageManager = NULL;

}


void InputSystem::update()
{
	static Vector2D lastPos(0.0f, 0.0f);
	static Vector2D goalPos(0.0f, 0.0f);
	al_get_mouse_state(&mMouse);
	al_get_keyboard_state(&mKey);

	if (firstPress(mMouse, mPrevMouse,1))
	{
		if (!firstSelect)
		{
			lastPos = Vector2D(mMouse.x, mMouse.y);
			firstSelect = true;
		}
		else
		{
			Vector2D pos(mMouse.x, mMouse.y);
			if (lastPos.getX() != pos.getX() || lastPos.getY() != pos.getY())
			{
				GameMessage* pMessage = new PathToMessage(lastPos, pos);
				mpMessageManager->addMessage(pMessage, 0);
				firstSelect = false;
				goalPos = Vector2D(mMouse.x, mMouse.y);
			}
		}

	}
	// drawing start and end goal and letters
	if (firstSelect)
	{
		Vector2D ulPos = gpGameA->getGrid()->getULCornerOfSquare(gpGameA->getGrid()->getSquareIndexFromPixelXY((int)lastPos.getX(), (int)lastPos.getY())); 
		al_draw_filled_rectangle(ulPos.getX(), ulPos.getY(), ulPos.getX() + 32, ulPos.getY() + 32, al_map_rgb(1, 255, 128));
		al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), ulPos.getX()+ 16, ulPos.getY(),ALLEGRO_ALIGN_CENTER, "S" );
	}
	else
	{
		Vector2D ulPos = gpGameA->getGrid()->getULCornerOfSquare(gpGameA->getGrid()->getSquareIndexFromPixelXY((int)lastPos.getX(), (int)lastPos.getY()));
		al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), ulPos.getX() + 16, ulPos.getY(), ALLEGRO_ALIGN_CENTER, "S");
		Vector2D ilPos = gpGameA->getGrid()->getULCornerOfSquare(gpGameA->getGrid()->getSquareIndexFromPixelXY((int)goalPos.getX(), (int)goalPos.getY()));
		al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), ilPos.getX() + 16, ilPos.getY(), ALLEGRO_ALIGN_CENTER, "G");
	}


	if (al_key_down(&mKey, ALLEGRO_KEY_ESCAPE))
	{
		gpGame->markForExit();
	}
	else if (firstPress( mKey, mPrevKey,ALLEGRO_KEY_D))
	{
		// not yet cuz nothin is there
		//GameMessage* pMessage = new SwitchPathFindingMessage(DijkstraPath);
		//mpMessageManager->addMessage(pMessage, 0);
	}
	else if (firstPress(mKey, mPrevKey, ALLEGRO_KEY_A))
	{
		// not yet cuz nothin is there
		//GameMessage* pMessage = new SwitchPathFindingMessage(AstarPath);
		//mpMessageManager->addMessage(pMessage, 0);
	}
	
	

	// assign last frames key
	mPrevKey = mKey;
	mPrevMouse = mMouse;
}

void InputSystem::draw()
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	//create mouse text


}

// only returns true if current keystate is down but not the last. same with mouse state
bool InputSystem::firstPress(ALLEGRO_KEYBOARD_STATE& now, ALLEGRO_KEYBOARD_STATE& last, int key)
{
	return ((al_key_down(&now, key)) && !(al_key_down(&last, key)));
}

bool InputSystem::firstPress(ALLEGRO_MOUSE_STATE& now, ALLEGRO_MOUSE_STATE& last, int mouseButton)
{
	return ((al_mouse_button_down(&now, mouseButton)) && !(al_mouse_button_down(&last, mouseButton)));
}
