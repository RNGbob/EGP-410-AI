
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

	al_get_mouse_state(&mMouse); 

	if (al_mouse_button_down(&mMouse, 1))
	{
		Vector2D pos(mMouse.x, mMouse.y);
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	else if (al_mouse_button_down(&mMouse, 2)){}


	al_get_keyboard_state(&mKey);

	if (al_key_down(&mKey, ALLEGRO_KEY_ESCAPE))
	{
		 gpGame->endGame();
	}
	else if (al_key_down(&mKey, ALLEGRO_KEY_LCTRL) || al_key_down(&mKey, ALLEGRO_KEY_RCTRL))//
	{
		if (firstPress(mKey, mPrevKey, ALLEGRO_KEY_S))
		{
			gpGame->getDataManager()->save();
		}
	}
	else if (firstPress(mKey, mPrevKey, ALLEGRO_KEY_I)) //
	{
		for (int i = 0; i < 5; ++i)
		{
			GameMessage* pMessage = new AddingMessage(Boids);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
	
	}
	else if (firstPress(mKey, mPrevKey, ALLEGRO_KEY_D))
	{
		GameMessage* pMessage = new DeletingMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	else if (firstPress(mKey, mPrevKey, ALLEGRO_KEY_P))
	{
		switchDebug();
	}
	else if (mDebuging)
	{
		if (firstPress(mKey, mPrevKey, ALLEGRO_KEY_C))// enemy velocity
		{
			mDebugVal = CohesionWeight;
		}
		else if (firstPress(mKey, mPrevKey, ALLEGRO_KEY_S))// reaction radius
		{
			mDebugVal = SeperateWeight;
		}
		else if (firstPress(mKey, mPrevKey, ALLEGRO_KEY_A))// angular velocity
		{
			mDebugVal = AlignWeight;
		}
		else if (firstPress(mKey, mPrevKey, ALLEGRO_KEY_MINUS))
		{
			GameMessage* pMessage = new DebugMessage(mDebugVal, -1);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
		else if (firstPress(mKey, mPrevKey, ALLEGRO_KEY_EQUALS) && ( al_key_down(&mKey, ALLEGRO_KEY_RSHIFT) || al_key_down(&mKey, ALLEGRO_KEY_LSHIFT)))
		{
			GameMessage* pMessage = new DebugMessage(mDebugVal, 1);
			MESSAGE_MANAGER->addMessage(pMessage, 0);
		}
	}
	
	// assign last frames key
	mPrevKey = mKey;
	mPrevMouse = mMouse;
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

		std::string d1 = "C : Cohesion Weight " + std::to_string(gpGame->getValue(CohesionWeight)),
			d2 = "S : Seperation Weight " + std::to_string(gpGame->getValue(SeperateWeight)),
			d3 = "A : Alignment Weight " + std::to_string(gpGame->getValue(AlignWeight));
		
		// draw text when debugging
		if (mDebuging)
		{
			al_draw_text(gpGame->getFont(), al_map_rgb(127, 0, 127), 30, 30, ALLEGRO_ALIGN_LEFT, "DEBUGGING ");
			al_draw_text(gpGame->getFont(), al_map_rgb(127, 0, 127), 30, 60, ALLEGRO_ALIGN_LEFT, "+/- : Add or subtract current value ");
			al_draw_text(gpGame->getFont(), al_map_rgb(127, 0, 127), 30, 90, ALLEGRO_ALIGN_LEFT, d1.c_str());//
			al_draw_text(gpGame->getFont(), al_map_rgb(127, 0, 127), 30, 120, ALLEGRO_ALIGN_LEFT, d2.c_str());//+ 
			al_draw_text(gpGame->getFont(), al_map_rgb(127, 0, 127), 30, 150, ALLEGRO_ALIGN_LEFT, d3.c_str());//+ 

		}


}

void InputSystem::switchDebug()
{
	mDebuging = !mDebuging;
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

/* 
		<<  << std::endl 
		<<  << std::endl
		<<  << std::endl
		<<  << std::endl
		<<  << std::endl
		<<  << std::endl
		;
*/