#include "DebugMessage.h"

DebugMessage::DebugMessage(ChangeableVal val, int mod)
:GameMessage(DEBUG_MESSAGE),
mVal(val),
mMod(mod)
{
}

DebugMessage::~DebugMessage()
{
}

void DebugMessage::process()
{
	gpGame->modValue(mVal, mMod);

}
