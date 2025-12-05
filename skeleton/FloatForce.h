#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class FloatForce : public ForceGenerator {
public:
	FloatForce(float h, float V, float d);

	void update(double time, Particle* p) override;
	void update(double time, PxRigidDynamic* r) override;//para solidos

	void setLiquidParticle(Particle* l);
	void addVol(float v);
	void setH(float h);
	 ~FloatForce();
protected:
	float _height;
	float _volume;
	float _liquid_density;
	float _gravity = -9.8;

	Particle* _liquid_particle; // For representation
};