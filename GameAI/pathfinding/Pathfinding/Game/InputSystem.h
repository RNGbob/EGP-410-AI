#ifndef INPUT_SYSTEM
#define INPUT_SYSTEM

#include "GraphicsSystem.h"
#include "GameApp.h"
#include <string>
#include <sstream>

class GameMessageManager;


class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	void init(GameMessageManager* &mesman);
	void cleanup();

	void update();
	void draw();

	bool firstPress(ALLEGRO_KEYBOARD_STATE& now, ALLEGRO_KEYBOARD_STATE& last, int key);
	bool firstPress(ALLEGRO_MOUSE_STATE& now, ALLEGRO_MOUSE_STATE& last, int mouseButton);

private:
	GameMessageManager* mpMessageManager;
	
	ALLEGRO_MOUSE_STATE mMouse;
	ALLEGRO_MOUSE_STATE mPrevMouse;

	ALLEGRO_KEYBOARD_STATE mKey;
	ALLEGRO_KEYBOARD_STATE mPrevKey;

	bool firstSelect;


};



#endif

