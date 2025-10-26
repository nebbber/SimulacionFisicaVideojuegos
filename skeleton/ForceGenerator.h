#pragma once
#include "Particle.h"
class ForceGenerator
{

public:
	//le paso tiempo y la particula a la que hay que aplicar la fuerza
	virtual void update(double t,Particle* p);
	

};

