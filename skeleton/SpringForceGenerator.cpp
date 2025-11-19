#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length) :_other(nullptr){
	_k = k;
	_rest_length = resting_length;
	
}

void SpringForceGenerator::update(double t, Particle* p) {
	
	Vector3 relative_pos_vector = _other->getPos() - p->getPos();
	Vector3 force;

	// normalize
	const float length = relative_pos_vector.normalize();
	const float delta_x = length - _rest_length;

	force = relative_pos_vector * delta_x * _k;

	p->addForce(force);
}

void SpringForceGenerator::setParticle(Particle* other)
{
	_other = other;
}
