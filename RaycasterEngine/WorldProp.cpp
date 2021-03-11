
#include "WorldProp.h"
#include "VMath.h"

// Overrides the default Entity tick() function, but calls it afterwards to keep any base behaviour
void WorldProp::tick()
{
	positon = body.getPosition();

	direction = VMath::lookAt(direction, playerRef->getPosition(), positon);	// Billboards towards the player

	Entity::tick();
}

