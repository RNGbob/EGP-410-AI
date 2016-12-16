#include "Game.h"
#include "Kinematic.h"
#include "KinematicUnit.h"
#include "Sprite.h"
#include "GraphicsSystem.h"
#include "Steering.h"
#include "UnitManager.h"
#include "WanderSteering.h"
#include "SeekSteering.h"
#include "Enemy.h"

using namespace std;

Steering gNullSteering( gZeroVector2D, 0.0f );

KinematicUnit::KinematicUnit(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, float maxVelocity, float maxAcceleration)
:Kinematic( position, orientation, velocity, rotationVel )
,mpSprite(pSprite)
,mpNormSprite(pSprite)
,mpCurrentSteering(NULL)
,mpGroupSteering(NULL)
,mMaxVelocity(maxVelocity)
,mMaxAcceleration(maxAcceleration)
,mIsPlayer(false)
,mActive(false)
,mDeltaPosition(Vector2D(0,0))
{
	mBox = BoxCollider(mPosition+Vector2D(2,2),Vector2D(GRID_SQUARE_SIZE-4, GRID_SQUARE_SIZE-4)); // slightly smaller to get through tight spots
}

KinematicUnit::~KinematicUnit()
{
	if (mpCurrentSteering != NULL && mpCurrentSteering != &gNullSteering)
	{
		delete mpCurrentSteering;
	}
	//delete mpGroupSteering;
}

void KinematicUnit::draw( GraphicsBuffer* pBuffer )
{
	mpSprite->draw( *pBuffer, mPosition.getX(), mPosition.getY(), mOrientation );
}

void KinematicUnit::update(float time)
{
	Steering* steering;
	mBox.setPos(mPosition);
	if( mpCurrentSteering != NULL )
	{
		steering = mpCurrentSteering->getSteering();
	}
	else
	{
		steering = &gNullSteering;
	}

	if( steering->shouldApplyDirectly() )
	{
		//not stopped
		if( getVelocity().getLengthSquared() > MIN_VELOCITY_TO_TURN_SQUARED )
		{
			setVelocity( steering->getLinear() );
			setOrientation( steering->getAngular() );
		}

		//since we are applying the steering directly we don't want any rotational velocity
		setRotationalVelocity( 0.0f );
		steering->setAngular( 0.0f );
	}
	

	//move the unit using current velocities
	Kinematic::update( time );
	//calculate new velocities
	calcNewVelocities( *steering, time, mMaxVelocity, 25.0f );


	//move to oposite side of screen if we are off
	//gpGame->getGraphicsSystem()->wrapCoordinates( mPosition );

	//set the orientation to match the direction of travel
	//setNewOrientation();
}

void KinematicUnit::modPosistion(Vector2D delta)
{
	// moving position and keeping track of current offset from current level
	mPosition += delta;
	mDeltaPosition += delta;
}

void KinematicUnit::setselfEnemy(Enemy * enemyptr)
{
	mpEnemyptr = enemyptr;
}

Enemy * KinematicUnit::getEnemyptr()
{
	return mpEnemyptr;
}

//private - deletes old Steering before setting
void KinematicUnit::setSteering( Steering* pSteering )
{
	if (mpCurrentSteering != NULL && mpCurrentSteering != &gNullSteering)
	{
		delete mpCurrentSteering;
	}
	
	mpCurrentSteering = pSteering;
}

void KinematicUnit::setGroupSteering(Steering* pSteering)
{
	delete mpGroupSteering;
	mpGroupSteering = pSteering;
}

float KinematicUnit::getDistance(KinematicUnit * other)
{
	Vector2D distanceVec = other->getPosition() - this->getPosition();
	float distance = distanceVec.getLength();
	return distance;
}

void KinematicUnit::setNewOrientation()
{ 
	mOrientation = getOrientationFromVelocity( mOrientation, mVelocity ); 
}

void KinematicUnit::wander()
{
	
	WanderSteering* pWanderSteering = new WanderSteering( this);
	setSteering( pWanderSteering );
}

void KinematicUnit::seek(KinematicUnit* target)
{
	

	SeekSteering* pSeekSteering = new SeekSteering( this, target );
	setSteering( pSeekSteering );
}
void KinematicUnit::flee(KinematicUnit * target)
{
	
	SeekSteering* pFleeSteering = new SeekSteering( this, target, true);
	setSteering(pFleeSteering);
}

void KinematicUnit::inActive()
{
	setSteering(&gNullSteering);
	mVelocity = Vector2D(0, 0);
	mPosition = Vector2D(-2000, -2000);
}

void KinematicUnit::switchSprite(Sprite * spr)
{
	if (spr == nullptr)
	{
		mpSprite = mpNormSprite;
	}
	else
	{
		mpSprite = spr;
	}
}

