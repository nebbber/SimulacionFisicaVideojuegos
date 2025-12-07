#include "SolidSystem.h"
#include "Gravity.h"
#include "ForceRegistry.h"
#include "Whirlwind.h"
SolidSystem::SolidSystem()
{
}

void SolidSystem::ActivateSolid(bool a)
{
	active = a;
}

SolidSystem::~SolidSystem()
{
	for (PxRigidActor* actor : bodies)
	{
		actor->release();
	}
	bodies.clear();

	delete _gravity;
	delete _whril;
	delete _oscillate;
	
}


