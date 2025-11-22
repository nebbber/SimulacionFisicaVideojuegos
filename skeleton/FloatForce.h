#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class FloatForce : public ForceGenerator {
public:
	FloatForce(float h, float V, float d);

	void update(double time, Particle* p);

	void setLiquidParticle(Particle* l);
	 ~FloatForce();
protected:
	float _height;
	float _volume;
	float _liquid_density;
	float _gravity = -9.8;

	Particle* _liquid_particle; // For representation
};