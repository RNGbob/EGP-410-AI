#include "Game.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "AddingMessage.h"
#include "InputSystem.h"


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
	if (mouse.buttons & 1)
	{
		Vector2D pos(mouse.x, mouse.y);
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	else if (mouse.buttons & 2){}

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

/*//**/

/*/
//get input - should be moved someplace better
ALLEGRO_MOUSE_STATE mouseState;
al_get_mouse_state(&mouseState);

if (al_mouse_button_down(&mouseState, 1))//left mouse click
{
	Vector2D pos(mouseState.x, mouseState.y);
	GameMessage* pMessage = new PlayerMoveToMessage(pos);
	MESSAGE_MANAGER->addMessage(pMessage, 0);
}



//all this should be moved to InputManager!!!
{
	//get mouse state
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	//create mouse text
	stringstream mousePos;
	mousePos << mouseState.x << ":" << mouseState.y;

	//write text at mouse position
	al_draw_text(mpFont, al_map_rgb(255, 255, 255), mouseState.x, mouseState.y, ALLEGRO_ALIGN_CENTRE, mousePos.str().c_str());

	mpGraphicsSystem->swap();

	//get current keyboard state
	ALLEGRO_KEYBOARD_STATE keyState;
	al_get_keyboard_state(&keyState);

	//if escape key was down then exit the loop
	if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
	{
		mShouldExit = true;
	}
} 
/**/