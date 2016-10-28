#pragma once

#include "Trackable.h"
#include "PerformanceTracker.h"
#include "Defines.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include "BoxCollider.h"
#include "CircleCollider.h"
#include <string>
#include <sstream>

class GraphicsSystem;
class GraphicsBuffer;
class GraphicsBufferManager;
class SpriteManager;
class KinematicUnit;
class GameMessageManager;
class Timer;
class UnitManager;
class InputSystem;
class WallManager;


const IDType BACKGROUND_SPRITE_ID = 0;
const IDType PLAYER_ICON_SPRITE_ID = 1;
const IDType AI_ICON_SPRITE_ID = 2;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

const int WIDTH = 1024;
const int HEIGHT = 768;


enum Method
{
	Arrive, Seek, Wander, WanderSeek, WanderFlee, Boids
};

enum ChangeableVal
{
	EnemyVel, ReactionRadius, AngularVel, AvoidRadius, AlignWeight, CohesionWeight, SeperateWeight
};

class Game:public Trackable
{
public:
	Game();
	~Game();

	bool init();//returns true if no errors, false otherwise
	void cleanup();

	//game loop
	void beginLoop();
	void processLoop();
	bool endLoop();

	inline GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };
	inline ALLEGRO_FONT* getFont() const { return mpFont; };
	inline void endGame(){ mShouldExit = true; }
	// changeble values for Assignment2 debug state.
	int getValue(ChangeableVal val);
	void setValue(ChangeableVal val , int direction);


	void input();
	void update();
	void draw();

	
	KinematicUnit* getPlayerUnit();
	UnitManager* getUnitManager();
	WallManager* getWallManager();
	/*/inline KinematicUnit* getAIUnit() { return mpAIUnit; };//should be someplace else
	inline KinematicUnit* getAIUnit2() { return mpAIUnit2; };//should be someplace else/**/



private:
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	GameMessageManager* mpMessageManager;
	UnitManager* mpUnitManager;
	InputSystem* mpInputSystem;
	WallManager* mpWallManager;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	bool mShouldExit;

	//should be somewhere else
	ALLEGRO_FONT* mpFont;
	ALLEGRO_SAMPLE* mpSample;
	IDType mBackgroundBufferID;
	IDType mPlayerIconBufferID;
	IDType mEnemyIconBufferID;

	// changeable values for gamestate;
	int mEnemyVel, mReactionRadius, mAngularVel, mAvoidRadius;
	int mAlignWeight, mCohesionWeight, mSeperateWeight;

	/*/
	KinematicUnit* mpUnit;
	KinematicUnit* mpAIUnit;
	KinematicUnit* mpAIUnit2;/**/
};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge

extern Game* gpGame;
extern PerformanceTracker* gpPerformanceTracker;

