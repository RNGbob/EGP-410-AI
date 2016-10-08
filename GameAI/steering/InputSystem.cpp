
#include "Game.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "AddingMessage.h"
#include "InputSystem.h"
#include <string>
#include <sstream>



InputSystem::InputSystem()
{
	mpMessageManger = nullptr;
}
InputSystem::~InputSystem(){}

void InputSystem::init( GameMessageManager* &mesman)
{
	mpMessageManger = mesman;
	mDebuging = false;
	mAdding = true;
	// make string streams




}

void InputSystem::cleanup()// easier to call rather than depending on destructor call;
{
	delete mpMessageManger;
	mpMessageManger = NULL;
	
}


void InputSystem::update()
{

	ALLEGRO_MOUSE_STATE mouse;

	al_get_mouse_state(&mouse); 

	if (al_mouse_button_down(&mouse, 1))
	{
		Vector2D pos(mouse.x, mouse.y);
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	else if (al_mouse_button_down(&mouse, 2)){}

	ALLEGRO_KEYBOARD_STATE key;

	al_get_keyboard_state(&key);

	 if (al_key_down(&key, ALLEGRO_KEY_ESCAPE))
	{
		 gpGame->endGame();
	}
	else if (al_key_down(&key, ALLEGRO_KEY_F))
	{
		GameMessage* pMessage = new AddingMessage(WanderFlee);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	else if (al_key_down(&key, ALLEGRO_KEY_S))
	{
		GameMessage* pMessage = new AddingMessage(WanderSeek);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	else if (al_key_down(&key, ALLEGRO_KEY_D))
	{
		GameMessage* pMessage = new DeletingMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	else if (mDebuging)
	{
		if (al_key_down(&key, ALLEGRO_KEY_F))
		{
			GameMessage* pMessage = new AddingMessage(WanderFlee);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		else if (al_key_down(&key, ALLEGRO_KEY_S))
		{
			GameMessage* pMessage = new AddingMessage(WanderSeek);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		else if (al_key_down(&key, ALLEGRO_KEY_D))
		{
			GameMessage* pMessage = new DeletingMessage();
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
	}
	
}

void InputSystem::draw()
{
		ALLEGRO_MOUSE_STATE mouseState;
		al_get_mouse_state( &mouseState );

		//create mouse text
		
		std::stringstream mousePos;
		mousePos << mouseState.x << ":" << mouseState.y;

		//write text at mouse position
		al_draw_text( gpGame->getFont(), al_map_rgb( 255, 255, 255 ), mouseState.x, mouseState.y, ALLEGRO_ALIGN_CENTRE, mousePos.str().c_str() );

}

void InputSystem::switchDebug()
{
	mDebuging = !mDebuging;
}

/* 
		
*/