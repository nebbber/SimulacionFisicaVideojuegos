#pragma once
#include "ParticleSystem.h"
class Gravity;
class FloatForce;
class FlotacionPracticaSystem : public ParticleSystem
{
private:

	Particle* agua;
	Particle* objeto;

public:
	FlotacionPracticaSystem(Gravity* g, FloatForce* f);
	
	void setMasa(float m);
	void update(double t) override;
	~FlotacionPracticaSystem();
};



