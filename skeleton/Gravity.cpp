#include "Gravity.h"

Gravity::Gravity(Vector3 g):gravity(0.0f,0.0f,0.0f)
{
	gravity = g;
}

Gravity::~Gravity()
{

}

void Gravity::update(double t, Particle* p)
{
	//le tengo que pasar una fuerza a la particula x para que le afecte en la acceleracion
	Vector3 f = p->getMasa() * gravity;
	p->addForce(f);

}
