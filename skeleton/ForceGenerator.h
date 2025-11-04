#pragma once
#include "Particle.h"
class ForceGenerator
{
protected:
	bool active;

public:
	//le paso tiempo y la particula a la que hay que aplicar la fuerza
	virtual void update(double t, Particle* p) {};
	void setActive(bool a) { active = a; };

};

