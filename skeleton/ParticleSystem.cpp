#include "ParticleSystem.h"
#include "Gravity.h"
#include "ForceRegistry.h"
#include "WindGenerator.h"
#include "Whirlwind.h"
#include "OscillateWind.h"
#include "ForceGenerator.h"
#include "ParticleGen.h"
#include "SpringForceGenerator.h"
#include <iostream>
using namespace std;
#include <cmath>
ParticleSystem::ParticleSystem()
{
	
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
	delete _oscillate;
	delete _spring1;
	delete _spring2;
	delete _spring3;
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

void ParticleSystem::ActivateSpring(bool a)
{
	_spring1->setActive(a);
	_spring2->setActive(a);
	_spring3->setActive(a);
}



