#include "ParticleSystem.h"
#include "Gravity.h"
#include "ForceRegistry.h"
#include "WindGenerator.h"
#include "Whirlwind.h"
#include "OscillateWind.h"
#include "ForceGenerator.h"
#include "ParticleGen.h"
#include "SpringForceGenerator.h"
#include "FloatForce.h"
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
	delete _float;
}

void ParticleSystem::ActivateParticle(bool a)
{
    active = a;
}

void ParticleSystem::ActivateGravity(bool a)
{
	if (_gravity)
	{
		_gravity->setActive(a);
	}

}

void ParticleSystem::ActivateOscilate(bool a)
{
	if (_oscillate)
	{
		_oscillate->setActive(a);
	}
}

void ParticleSystem::ActivateWind(bool a)
{
	if (_wind)
	{
		_wind->setActive(a);
	}
}

void ParticleSystem::ActivateSpring(bool a)
{
	if (_spring1)
	{
		_spring1->setActive(a);
	}

	if (_spring2)
	{
		_spring2->setActive(a);
	}

	if (_spring3)
	{
		_spring3->setActive(a);
	}
}

void ParticleSystem::ActivateFloat(bool a)
{
	if (_float)
	{
		_float->setActive(a);
	}
}



