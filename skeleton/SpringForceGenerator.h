#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class SpringForceGenerator :public ForceGenerator {
public:
	SpringForceGenerator(double k, double resting_length);

	 void update(double t, Particle* p) override;
	void setParticle(Particle* other);
	inline void setK(double k) { _k = k; }

	virtual ~SpringForceGenerator() {}
protected:
	double _k;
	double _rest_length;
	Particle* _other;
};