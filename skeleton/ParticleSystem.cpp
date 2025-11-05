#include "ParticleSystem.h"
#include "Gravity.h"
#include "ForceRegistry.h"
#include "WindGenerator.h"
#include "Whirlwind.h"
#include "OscillateWind.h"
#include "ForceGenerator.h"
#include <iostream>
using namespace std;
#include <cmath>
ParticleSystem::ParticleSystem()
{
	//_registry = registry;
}

ParticleSystem::~ParticleSystem()
{

	for (Particle* p : _particles)
	{
		delete p;
	}

	_particles.clear();

	for (ParticleGen* g : _generators)
	{
		delete g;
	}

	_generators.clear();
	delete _gravity;
	delete _wind;
//	delete _whril;
	delete _oscillate;
}

void ParticleSystem::ActivateParticle(bool a)
{
    active = a;
}

void ParticleSystem::ActivateGravity(bool a)
{
    _gravity->setActive(a);
}

void ParticleSystem::ActivateOscilate(bool a)
{
    _oscillate->setActive(a);
}

void ParticleSystem::ActivateWind(bool a)
{
	_wind->setActive(a);
}



