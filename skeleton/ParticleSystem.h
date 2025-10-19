#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGen.h"
#include "GaussianGen.h"
class ParticleSystem
{
private:
	std::list<Particle*> _particles;
	std::list<Particle*> nuevasParticulas;
	std::list<ParticleGen*> _generators;
	GaussianGen* pg;
public:
	ParticleSystem();
	void update(double t);// te recorres todas y cunado sea no alive la borras
	~ParticleSystem();

};

