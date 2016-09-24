#ifndef INPUT_SYSTEM
#define INPUT_SYSTEM

#include "GraphicsSystem.h"
#include "Game.h"

class GameMessageManager;


class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	void init(GameMessageManager* &mesman);
	void cleanup();
	
	void update();

private:
	GameMessageManager* mpMessageManger;

};



#endif