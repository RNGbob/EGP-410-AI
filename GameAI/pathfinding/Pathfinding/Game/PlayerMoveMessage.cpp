#include "PlayerMoveMessage.h"
#include "GameApp.h"
#include "Player.h"

PlayerMoveMessage::PlayerMoveMessage(const Vector2D & direction)
:GameMessage(PLAYER_MOVE_MESSAGE),
mDirection(direction)
{
}

void PlayerMoveMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);

	pGame->getPlayerUnit()->setVelocity(mDirection); // *maxVelocity;
}
