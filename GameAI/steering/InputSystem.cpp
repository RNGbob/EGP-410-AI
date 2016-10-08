
#include "Game.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "AddingMessage.h"
#include "DebugMessage.h"
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
	else if (al_key_down(&key, ALLEGRO_KEY_I))
	{
		switchDebug();
	}
	else if (mDebuging)
	{
		if (al_key_down(&key, ALLEGRO_KEY_V))// enemy velocity
		{
			mDebugVal = EnemyVel;
		}
		else if (al_key_down(&key, ALLEGRO_KEY_R))// reaction radius
		{
			mDebugVal = ReactionRadius;
		}
		else if (al_key_down(&key, ALLEGRO_KEY_A))// angular velocity
		{
			mDebugVal = AngularVel;
		}
		else if (al_key_down(&key, ALLEGRO_KEY_B)) // Avoid radius
		{
			mDebugVal = AvoidRadius;
		}
		else if (al_key_down(&key, ALLEGRO_KEY_MINUS)) 
		{
			GameMessage* pMessage = new DebugMessage(mDebugVal, -1);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		else if (al_key_down(&key, ALLEGRO_KEY_EQUALS)) 
		{
			GameMessage* pMessage = new DebugMessage(mDebugVal, 1);
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

		std::string d1 = "V : Enemy Velocity " + std::to_string(gpGame->getValue(EnemyVel)),
			d2 = "R : Reaction Radius " + std::to_string(gpGame->getValue(ReactionRadius)),
			d3 = "A : Angular Velocity " + std::to_string(gpGame->getValue(AngularVel)),
			d4 = "B : Seperation Strength " + std::to_string(gpGame->getValue(AvoidRadius));
		
		
		
		
		if (mDebuging)
		{
			al_draw_text(gpGame->getFont(), al_map_rgb(127, 0, 127), 30, 30, ALLEGRO_ALIGN_LEFT, "DEBUGGING ");
			al_draw_text(gpGame->getFont(), al_map_rgb(127, 0, 127), 30, 60, ALLEGRO_ALIGN_LEFT, "+/- : Add or subtract current value ");
			al_draw_text(gpGame->getFont(), al_map_rgb(127, 0, 127), 30, 90, ALLEGRO_ALIGN_LEFT, d1.c_str());//
			al_draw_text(gpGame->getFont(), al_map_rgb(127, 0, 127), 30, 120, ALLEGRO_ALIGN_LEFT, d2.c_str());//+ 
			al_draw_text(gpGame->getFont(), al_map_rgb(127, 0, 127), 30, 150, ALLEGRO_ALIGN_LEFT, d3.c_str());//+ 
			al_draw_text(gpGame->getFont(), al_map_rgb(127, 0, 127), 30, 180, ALLEGRO_ALIGN_LEFT, d4.c_str());//+

		}


}

void InputSystem::switchDebug()
{
	mDebuging = !mDebuging;
}

/* 
		<<  << std::endl 
		<<  << std::endl
		<<  << std::endl
		<<  << std::endl
		<<  << std::endl
		<<  << std::endl
		;
*/