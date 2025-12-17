#pragma once
#include "ParticleSystem.h"
class Gravity;
class OscillateWind;
class GaussianGen;
class MuellePracticaSystem : public ParticleSystem
{
private:

	Particle* ptoAnclajeCubo;
	Particle* p1Muelles;
	Particle* p2Muelles;

public:
	MuellePracticaSystem(Gravity* g, SpringForceGenerator* s1, SpringForceGenerator* s2);

	void update(double t) override;
	~MuellePracticaSystem();
	void setK(int K);
};

