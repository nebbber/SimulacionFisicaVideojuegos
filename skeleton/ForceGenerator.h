#pragma once
#include "Particle.h"
#include "PxPhysicsAPI.h"
class ForceGenerator
{
protected:
	bool active=true;

public:
	//le paso tiempo y la particula a la que hay que aplicar la fuerza
	virtual void update(double t, Particle* p) {};
	virtual void update(double t, PxRigidDynamic* r) {}; //para solido rígidos
	bool isActive() { return active; };
	void setActive(bool a) { active = a; };

};

