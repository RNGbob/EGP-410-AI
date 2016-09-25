#include "Game.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "AddingMessage.h"
#include "InputSystem.h"
#include <sstream>



InputSystem::InputSystem()
{
	mpMessageManger = nullptr;
}
InputSystem::~InputSystem(){}

void InputSystem::init( GameMessageManager* &mesman)
{
	mpMessageManger = mesman;
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
	else if (al_key_down(&key, ALLEGRO_KEY_A))
	{
		GameMessage* pMessage = new AddingMessage(Arrive);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	else if (al_key_down(&key, ALLEGRO_KEY_S))
	{
		GameMessage* pMessage = new AddingMessage(Seek);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	else if (al_key_down(&key, ALLEGRO_KEY_D))
	{
		GameMessage* pMessage = new DeletingMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	
}

