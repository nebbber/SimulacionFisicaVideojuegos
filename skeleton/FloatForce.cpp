#include "FloatForce.h"
FloatForce::FloatForce(float h, float V, float d):_liquid_particle(nullptr)
{
	_height = h;//del agua
	_volume = V;
	_liquid_density = d;

}
void FloatForce::update(double time, Particle* p) {
	float h = p->getPos().y;
	float h0 = _liquid_particle->getPos().y;


	Vector3 f(0, 0, 0);
	float immersed = 0.0;
	if (h - h0 > _height * 0.5) { //no inmersa
		immersed = 0.0;
	}
	else if (h0 - h > _height * 0.5) {
		// Totally immersed
		immersed = 1.0;
	}
	else { //parte inversa
		immersed = (h0 - h) / _height + 0.5;

	}
	f.y = _liquid_density * _volume * immersed * 9.8;

	p->addForce(f);
}

void FloatForce::update(double time, PxRigidDynamic* r)
{
	if (!r || !_liquid_particle) return;

	float h = r->getGlobalPose().p.y;          // posición del rígido
	float h0 = _liquid_particle->getPos().y;   // superficie del agua

	float immersed = 0.0f;

	if (h - h0 > _height * 0.5f) {
		immersed = 0.0f;
	}
	else if (h0 - h > _height * 0.5f) {
		immersed = 1.0f;
	}
	else {
		immersed = (h0 - h) / _height + 0.5f;
	}

	// fuerza de flotación
	float Fy = _liquid_density * _volume * immersed * 9.8f;

	PxVec3 force(0.0f, Fy, 0.0f);
	r->addForce(force);
}

void FloatForce::setLiquidParticle(Particle* l)
{
	_liquid_particle = l;
}

void FloatForce::addVol(float v)
{
	_volume += v;
}


FloatForce::~FloatForce()
{
}
