#pragma once
#include "ParticleSystem.h"
class Gravity;
class WindGenerator;
class UniformGen;
class SnowSystem : public ParticleSystem
{
private:

	UniformGen* snow;
	

public:
	SnowSystem(Gravity* g, WindGenerator* o);

	void update(double t) override;
	~SnowSystem();

	void addForceGenerator(ForceGenerator* fg);
};


