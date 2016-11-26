#include "Enemy.h"
#include "GameApp.h"

Enemy::Enemy(Sprite *pSprite, const Vector2D &position, float orientation, const Vector2D &velocity, float rotationVel, float maxVelocity, float maxAcceleration)
: KinematicUnit(pSprite, position, orientation, velocity, rotationVel,  maxVelocity,  maxAcceleration)
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	mpPlayer = pGame->getPlayerUnit();

}

Enemy::~Enemy()
{
}
