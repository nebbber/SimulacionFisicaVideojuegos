#include "SolidSystem.h"

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
		///scene->removeActor(*actor);  
		actor->release();             
	}
	bodies.clear();

	delete _gravity;
	
}


