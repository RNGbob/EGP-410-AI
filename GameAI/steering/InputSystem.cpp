#pragma once
#include "InputSystem.h"


InputSystem::InputSystem()
{
	mpMessageManger = nullptr;
}
InputSystem::~InputSystem()
{
	//al_uninstall_mouse();
	//al_uninstall_keyboard();
}

void InputSystem::init(GameMessageManager* &mesman)
{
	//al_install_mouse();   
	//al_install_keyboard();

	mpMessageManger = mesman;
}

void InputSystem::cleanup()
{
	delete mpMessageManger;
	mpMessageManger = NULL;
	
}


void InputSystem::update()
{

	ALLEGRO_MOUSE_STATE mouse;

	al_get_mouse_state(&mouse); 
	if (mouse.buttons & 1)
	{
		
	}
	
	else if (mouse.buttons & 2)
	{
		
	}

	ALLEGRO_KEYBOARD_STATE key;

	al_get_keyboard_state(&key);

	if ( al_key_down(&key, ALLEGRO_KEY_SPACE))
	{
		
	}
	
	else if (al_key_down(&key, ALLEGRO_KEY_ESCAPE))
	{
		
	}
	else if (al_key_down(&key, ALLEGRO_KEY_UP))
	{
		
	}
	else if (al_key_down(&key, ALLEGRO_KEY_DOWN))
	{
		
	}
	else if (al_key_down(&key, ALLEGRO_KEY_LEFT))
	{
		
	}
	else if (al_key_down(&key, ALLEGRO_KEY_RIGHT))
	{
		
	}
}