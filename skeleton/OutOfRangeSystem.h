#pragma once
#include "ParticleSystem.h"
class Gravity;
class WindGenerator;
class OscillateWind;
class UniformGen;
class OutOfRangeSystem : public ParticleSystem
{
private:

	UniformGen* p;
	

public:
	OutOfRangeSystem(Gravity* g, WindGenerator* w, OscillateWind* o);

	void update(double t) override;
	~OutOfRangeSystem();

	void addForceGenerator(ForceGenerator* fg);
};


