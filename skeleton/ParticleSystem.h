#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGen.h"
class ParticleSystem
{
private:
	std::list<Particle*> _particles;
	std::list<ParticleGen*> _generators;
	
public:
	void update(double t);
};

