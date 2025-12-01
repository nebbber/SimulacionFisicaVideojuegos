#include "SolidSystem.h"

SolidSystem::SolidSystem()
{
}

SolidSystem::~SolidSystem()
{
}

void SolidSystem::update(float dt)
{

}


void SolidSystem::addRigidBody(PxRigidActor* rb)
{
	bodies.push_back(rb);
}
