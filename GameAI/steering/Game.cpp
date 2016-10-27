#include <stdio.h>
#include <assert.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <sstream>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "GameMessageManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "UnitManager.h"
#include "InputSystem.h"
#include "WallManager.h"
#include "Timer.h"
#include "KinematicUnit.h"
#include "PlayerMoveToMessage.h"

Game* gpGame = NULL;

const int WIDTH = 1024;
const int HEIGHT = 768;

Game::Game()
	:mpGraphicsSystem(NULL)
	,mpGraphicsBufferManager(NULL)
	,mpSpriteManager(NULL)
	,mpLoopTimer(NULL)
	,mpMasterTimer(NULL)
	,mShouldExit(false)
	,mpFont(NULL)
	,mpSample(NULL)
	,mBackgroundBufferID(INVALID_ID)
	, mEnemyVel(150)
	, mReactionRadius(250)
	, mAngularVel(10)
	, mAvoidRadius(250)
	, mAlignWeight(1)
	, mCohesionWeight(1)
	, mSeperateWeight(2)
	//,mSmurfBufferID(INVALID_ID)
{
}

Game::~Game()
{
	cleanup();
}

bool Game::init()
{
	mShouldExit = false;

	//create Timers
	mpLoopTimer = new Timer;
	mpMasterTimer = new Timer;

	//startup allegro
	if(!al_init()) 
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return false;
	}

	//create and init GraphicsSystem
	mpGraphicsSystem = new GraphicsSystem();
	bool goodGraphics = mpGraphicsSystem->init( WIDTH, HEIGHT );
	if(!goodGraphics) 
	{
		fprintf(stderr, "failed to initialize GraphicsSystem object!\n");
		return false;
	}

	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpSpriteManager = new SpriteManager();
	
	// initializing ne managers
	mpUnitManager = new UnitManager();
	mpInputSystem = new InputSystem();
	mpWallManager = new WallManager();
	
	
	//startup a lot of allegro stuff

	//load image loader addon
	if( !al_init_image_addon() )
	{
		fprintf(stderr, "image addon failed to load!\n");
		return false;
	}

	//install audio stuff
	if( !al_install_audio() )
	{
		fprintf(stderr, "failed to initialize sound!\n");
		return false;
	}

	if(!al_init_acodec_addon())
	{
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return false;
	}
 
	if (!al_reserve_samples(1))
	{
		fprintf(stderr, "failed to reserve samples!\n");
		return false;
	}

	//should probably be done in the InputSystem!
	if( !al_install_keyboard() )
	{
		printf( "Keyboard not installed!\n" ); 
		return false;
	}

	//should probably be done in the InputSystem!
	if( !al_install_mouse() )
	{
		printf( "Mouse not installed!\n" ); 
		return false;
	}

	//should be somewhere else!
	al_init_font_addon();
	if( !al_init_ttf_addon() )
	{
		printf( "ttf font addon not initted properly!\n" ); 
		return false;
	}

	//actually load the font
	mpFont = al_load_ttf_font( "cour.ttf", 20, 0 );
	if( mpFont == NULL )
	{
		printf( "ttf font file not loaded properly!\n" ); 
		return false;
	}

	//show the mouse
	if( !al_hide_mouse_cursor( mpGraphicsSystem->getDisplay() ) )
	{
		printf( "Mouse cursor not able to be hidden!\n" ); 
		return false;
	}

	if( !al_init_primitives_addon() )
	{
		printf( "Primitives addon not added!\n" ); 
		return false;
	}

	//load the sample
	mpSample = al_load_sample( "clapping.wav" );
	if (!mpSample)
	{
		printf( "Audio clip sample not loaded!\n" ); 
		return false;
	}

	mpMessageManager = new GameMessageManager();

	// input takes message manager
	mpInputSystem->init(mpMessageManager);



	//load buffers
	mBackgroundBufferID = mpGraphicsBufferManager->loadBuffer("wallpaper.bmp");
	mPlayerIconBufferID = mpGraphicsBufferManager->loadBuffer("arrow.bmp");
	mEnemyIconBufferID = mpGraphicsBufferManager->loadBuffer("enemy-arrow.bmp");
	
	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( mBackgroundBufferID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
	}
	GraphicsBuffer* pPlayerBuffer = mpGraphicsBufferManager->getBuffer( mPlayerIconBufferID );
	Sprite* pArrowSprite = NULL;
	if( pPlayerBuffer != NULL )
	{
		pArrowSprite = mpSpriteManager->createAndManageSprite( PLAYER_ICON_SPRITE_ID, pPlayerBuffer, 0, 0, pPlayerBuffer->getWidth(), pPlayerBuffer->getHeight() );
	}
	GraphicsBuffer* pAIBuffer = mpGraphicsBufferManager->getBuffer( mEnemyIconBufferID );
	Sprite* pEnemyArrow = NULL;
	if( pAIBuffer != NULL )
	{
		pEnemyArrow = mpSpriteManager->createAndManageSprite( AI_ICON_SPRITE_ID, pAIBuffer, 0, 0, pAIBuffer->getWidth(), pAIBuffer->getHeight() );
	}
	
	// units reference spritemanager when creating entities
	mpUnitManager->init( mpSpriteManager); 

	//construct walls
	//mpWallManager->addWall(Vector2D(), Vector2D(), 50.0f);
	mpWallManager->addWall(Vector2D(0,0), Vector2D(WIDTH,0), 50.0f);
	mpWallManager->addWall(Vector2D(0,0), Vector2D(0,HEIGHT), 50.0f);
	mpWallManager->addWall(Vector2D(0,HEIGHT), Vector2D(WIDTH,HEIGHT), 50.0f);
	mpWallManager->addWall(Vector2D(WIDTH,0), Vector2D(WIDTH,HEIGHT), 50.0f);
	
	return true;
}

KinematicUnit* Game::getPlayerUnit()
{
	return mpUnitManager->getPlayer();
}

UnitManager* Game::getUnitManager()
{
	return mpUnitManager;
}

WallManager * Game::getWallManager()
{
	return mpWallManager;
}

void Game::cleanup()
{
	//delete unitmanager/Inputsystem
	//mpUnitManager->cleanup();
	delete mpUnitManager;
	mpUnitManager = NULL;
	//mpInputSystem->cleanup();
	delete mpInputSystem;
	mpInputSystem = NULL;

	delete mpWallManager;
	mpWallManager = NULL;
	
	//delete the timers
	delete mpLoopTimer;
	mpLoopTimer = NULL;
	delete mpMasterTimer;
	mpMasterTimer = NULL;

	//delete the graphics system
	delete mpGraphicsSystem;
	mpGraphicsSystem = NULL;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = NULL;
	delete mpSpriteManager;
	mpSpriteManager = NULL;
	delete mpMessageManager;
	mpMessageManager = NULL;

	

	al_destroy_sample(mpSample);
	mpSample = NULL;
	al_destroy_font(mpFont);
	mpFont = NULL;

	//shutdown components
	al_uninstall_audio();
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_shutdown_primitives_addon();

}

void Game::beginLoop()
{
	mpLoopTimer->start();
}

int Game::getValue(ChangeableVal val)
{
	switch (val)
	{
	case EnemyVel:
		return mEnemyVel;
		break;
	case ReactionRadius:
		return mReactionRadius;
		break;
	case AngularVel:
		return mAngularVel;
		break;
	case AvoidRadius:
		return mAvoidRadius;
		break;
	default:
		break;
	}
	
	
	
	return 0;
}

void Game::setValue(ChangeableVal val, int direction) // direction is either 1 or -1
{
	int speed = 1;
	switch (val)
	{
	case EnemyVel:
		mEnemyVel += (direction*speed);
		mpUnitManager->changeVels1(mEnemyVel);
		break;
	case ReactionRadius:
		mReactionRadius += (direction*speed);
		break;
	case AngularVel:
		mAngularVel += (direction*speed);
		break;
	case AvoidRadius:
		mAvoidRadius += (direction*speed);
		break;
	default:
		break;
	}


}

// These will be put into processLoop
void  Game::input()
{
	mpInputSystem->update();
}

void  Game::update()
{
	mpUnitManager->update(LOOP_TARGET_TIME / 1000.0f);
}
void  Game::draw()
{
	Sprite* pBackgroundSprite = mpSpriteManager->getSprite(BACKGROUND_SPRITE_ID);
	pBackgroundSprite->draw(*(mpGraphicsSystem->getBackBuffer()), 0, 0);
	
	mpUnitManager->draw(GRAPHICS_SYSTEM->getBackBuffer());
	mpWallManager->draw();
	mpInputSystem->draw();

	

}

/**//**/

void Game::processLoop() //order is either update,draw, processMsg,input OR update,draw.input, processMsg 
{
	/*/
	/**/
	// replacing entirety of old method
	update();
	draw();
	mpMessageManager->processMessagesForThisframe();
	input();
	//al_draw_line(100.0f, 0.0f, 500.0f, 0.0f, al_map_rgb(127,0,127), 50.0f);
	mpGraphicsSystem->swap();

	/*/
	/**/
}

bool Game::endLoop()
{
	//mpMasterTimer->start();
	mpLoopTimer->sleepUntilElapsed( LOOP_TARGET_TIME );
	return mShouldExit;
}

float genRandomBinomial()
{
	return genRandomFloat() - genRandomFloat();
}

float genRandomFloat()
{
	float r = (float)rand()/(float)RAND_MAX;
	return r;
}

