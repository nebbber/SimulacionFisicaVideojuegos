#include "SolidSystem.h"
#include "Gravity.h"
#include "ForceRegistry.h"
#include "OscillateWind.h"
SolidSystem::SolidSystem()
{
}
void SolidSystem::ActivateSolid(bool a)
{
	active = a;
}
void SolidSystem::ActivateGravity(bool a)
{
	if (_gravity)
	{
		_gravity->setActive(a);
	}

}
bool SolidSystem::isActive()
{
	return active;
}

void SolidSystem::ActivateOscilate(bool a)
{
	if (_oscillate)
	{
		_oscillate->setActive(a);
	}
}
SolidSystem::~SolidSystem()
{
	for (PxRigidActor* actor : bodies)
	{
		actor->release();
	}
	bodies.clear();

	
}


