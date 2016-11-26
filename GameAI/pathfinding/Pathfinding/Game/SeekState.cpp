#include "SeekState.h"

void SeekState::onEntrance()
{
	mpMover->seek(mpTarget);
}

void SeekState::onExit()
{

}

StateTransition * SeekState::update()
{
	// if outside of view range transition to wander
	// if powered up transition to flee;
	
	
	return nullptr;
}
