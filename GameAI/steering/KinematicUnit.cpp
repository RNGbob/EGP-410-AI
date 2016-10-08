#include "Game.h"
#include "Kinematic.h"
#include "KinematicUnit.h"
#include "Sprite.h"
#include "GraphicsSystem.h"
#include "Steering.h"
#include "KinematicSeekSteering.h"
#include "KinematicArriveSteering.h"
#include "KinematicWanderSteering.h"
#include "DynamicSeekSteering.h"
#include "DynamicArriveSteering.h"
#include "DynamicWanderSeekSteering.h"
#include "UnitManager.h"
#include "WallManager.h"

using namespace std;

Steering gNullSteering( gZeroVector2D, 0.0f );

KinematicUnit::KinematicUnit(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, float maxVelocity, float maxAcceleration)
:Kinematic( position, orientation, velocity, rotationVel )
,mpSprite(pSprite)
,mpCurrentSteering(NULL)
,mpGroupSteering(NULL)
,mMaxVelocity(maxVelocity)
,mMaxAcceleration(maxAcceleration)
,mIsPlayer(false)
{
	mDimension = pSprite->getDim();
}

KinematicUnit::~KinematicUnit()
{
	delete mpCurrentSteering;
	//delete mpGroupSteering;
}

void KinematicUnit::draw( GraphicsBuffer* pBuffer )
{
	mpSprite->draw( *pBuffer, mPosition.getX(), mPosition.getY(), mOrientation );
}

void KinematicUnit::update(float time, const std::vector<KinematicUnit*> &units)
{
	Steering* steering;
	if( mpCurrentSteering != NULL )
	{
		//steering = mpCurrentSteering->getSteering();
		steering = appliedSeperation(units); // determines steering with seperation from surrounding units
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
	if (gpGame->getWallManager()->checkCollision(this))
	{
		//cout << "COLLISION";
		Vector2D bounce = mVelocity*-3;
		this->setVelocity(bounce);
		steering= &gNullSteering;
	}

	//move the unit using current velocities
	Kinematic::update( time );
	//calculate new velocities
	calcNewVelocities( *steering, time, mMaxVelocity, 25.0f );


	//move to oposite side of screen if we are off
	GRAPHICS_SYSTEM->wrapCoordinates( mPosition );

	//set the orientation to match the direction of travel
	//setNewOrientation();
}

//private - deletes old Steering before setting
void KinematicUnit::setSteering( Steering* pSteering )
{
	delete mpCurrentSteering;
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

void KinematicUnit::seek(const Vector2D &target)
{
	KinematicSeekSteering* pSeekSteering = new KinematicSeekSteering( this, target );
	setSteering( pSeekSteering );
}

void KinematicUnit::arrive(const Vector2D &target)
{
	KinematicArriveSteering* pArriveSteering = new KinematicArriveSteering( this, target );
	setSteering( pArriveSteering );
}

void KinematicUnit::wander()
{
	KinematicWanderSteering* pWanderSteering = new KinematicWanderSteering( this );
	setSteering( pWanderSteering );
}

void KinematicUnit::dynamicSeek( KinematicUnit* pTarget )
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering( this, pTarget);//gpGame->getPlayerUnit()
	setSteering( pDynamicSeekSteering );
}

void KinematicUnit::dynamicFlee( KinematicUnit* pTarget )
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering( this, pTarget, true );
	setSteering( pDynamicSeekSteering );
}

void KinematicUnit::dynamicArrive( KinematicUnit* pTarget )
{
	DynamicArriveSteering* pDynamicArriveSteering = new DynamicArriveSteering( this, pTarget );
	setSteering( pDynamicArriveSteering );
}

void KinematicUnit::wanderSeek(KinematicUnit * pTarget)
{
	DynamicWanderSeekSteering* pDynamicWanderSeekSteering = new DynamicWanderSeekSteering(this, pTarget);
	setSteering(pDynamicWanderSeekSteering);

}

void KinematicUnit::wanderFlee(KinematicUnit * pTarget)
{
	DynamicWanderSeekSteering* pDynamicWanderSeekSteering = new DynamicWanderSeekSteering(this, pTarget, true);
	setSteering(pDynamicWanderSeekSteering);

}


// applies seperation for all nonplayer entities on a seperate steering copied from current steering

Steering * KinematicUnit::appliedSeperation(const std::vector<KinematicUnit*>& units)
{

	//delete mpGroupSteering;
	
	mpGroupSteering = mpCurrentSteering;
	
	Vector2D direction;
	float distance, strength;
	
	if (!mIsPlayer)
	{

		for (int i = 0; i < units.size(); ++i)
		{
			direction = units[i]->getPosition() - this->getPosition();
			distance = direction.getLength();
			if (distance < gpGame->getValue(AvoidRadius))
			{
				strength = min(250*distance*distance, this->mMaxAcceleration);// arbitrary decay coefficient
				
				direction.normalize();

				mpGroupSteering->setLinear(mpGroupSteering->getLinear() + (direction*strength));
			}
		}

		return mpGroupSteering->getSteering();;

	}
	else { return mpCurrentSteering->getSteering(); }
	
	return  mpCurrentSteering->getSteering();;
}



// suedo arbitration thing
/*
Steering* KinematicUnit::determineSteering(const std::vector<KinematicUnit*> &units)
{
	
	delete mpGroupSteering;
	mpGroupSteering = NULL;
	KinematicUnit* closest = nullptr;
	float smallest = 50.0f; // arbitrary for now 
	
	if (!mIsPlayer)
	{
		for (int i = 0; i < units.size(); ++i)
		{
			if (getDistance(units[i]) < smallest)
			{
				closest = units[i];
				smallest = getDistance(units[i]);
			}
		}
		if (closest != nullptr)
		{
			DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering(this, closest, true); 
			setGroupSteering(pDynamicSeekSteering);

			return mpGroupSteering->getSteering();
		}
		return mpCurrentSteering->getSteering();

	}
	else {return mpCurrentSteering->getSteering();}

}*/