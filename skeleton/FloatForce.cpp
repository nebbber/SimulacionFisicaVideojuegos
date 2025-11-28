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

void FloatForce::setLiquidParticle(Particle* l)
{
	_liquid_particle = l;
}

void FloatForce::setVol(float v)
{
	_volume = v;
}


FloatForce::~FloatForce()
{
}
