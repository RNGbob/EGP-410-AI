#include "Game.h"


InputSystem::InputSystem()
{
	
}
InputSystem::~InputSystem()
{
	al_uninstall_mouse();
	al_uninstall_keyboard();
}

void InputSystem::init()
{
	al_install_mouse();
	al_install_keyboard();
}

void InputSystem::update()
{

	ALLEGRO_MOUSE_STATE mouse;

	al_get_mouse_state(&mouse); 
	if (mouse.buttons & 1)
	{
		//gpEventSystem->fireEvent(AddEvent(Vector2D(mouse.x, mouse.y)));
		// add unit
	}
	
	else if (mouse.buttons & 2)
	{
		//gpEventSystem->fireEvent(DeleteEvent(Vector2D(mouse.x, mouse.y)));
		// delete unit
	}

	ALLEGRO_KEYBOARD_STATE key;

	al_get_keyboard_state(&key);

	if ( al_key_down(&key, ALLEGRO_KEY_SPACE))
	{
		//gpEventSystem->fireEvent(AddEvent(Vector2D(0,0)));
		//freeze event
	}
	
	else if (al_key_down(&key, ALLEGRO_KEY_ESCAPE))
	{
		gpEventSystem->fireEvent(QuitEvent());
		//quit event
	}
	else if (al_key_down(&key, ALLEGRO_KEY_UP))
	{
		gpEventSystem->fireEvent(TurnEvent(UP));
	}
	else if (al_key_down(&key, ALLEGRO_KEY_DOWN))
	{
		gpEventSystem->fireEvent(TurnEvent(DOWN));
	}
	else if (al_key_down(&key, ALLEGRO_KEY_LEFT))
	{
		gpEventSystem->fireEvent(TurnEvent(LEFT));
	}
	else if (al_key_down(&key, ALLEGRO_KEY_RIGHT))
	{
		gpEventSystem->fireEvent(TurnEvent(RIGHT));
	}
}