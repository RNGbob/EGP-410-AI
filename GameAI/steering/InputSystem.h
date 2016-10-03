#ifndef INPUT_SYSTEM
#define INPUT_SYSTEM

#include "GraphicsSystem.h"
#include "Game.h"
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

private:
	GameMessageManager* mpMessageManger;

};



#endif