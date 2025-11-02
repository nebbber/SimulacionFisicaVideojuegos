#include "ParticleSystem.h"
#include "Gravity.h"
#include "ForceRegistry.h"
#include "WindGenerator.h"
#include "Whirlwind.h"
#include <iostream>
using namespace std;

ParticleSystem::ParticleSystem(ForceRegistry* registry)
{
	_registry = registry;
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
	delete _whril;
}
void ParticleSystem::setGravity(Gravity* g)
{
	if (_gravity) delete _gravity;
	_gravity = g;
}

void ParticleSystem::setWind(WindGenerator* w)
{
	if (_wind) delete _wind;
	_wind = w;
}

void ParticleSystem::setWhril(Whirlwind* ww)
{
	if (_whril) delete _whril;
	_whril = ww;
}


void ParticleSystem::update(double t)
{

	for (ParticleGen* gen : _generators)
	{
		auto g = gen->generateP();

		for (Particle* p : g)
		{
			p->setGeometry();
			_particles.push_back(p);

			/**if (_whril)
				_registry->addGeneratorToParticle(_whril, p);
			if (_wind)*/
				_registry->addGeneratorToParticle(_wind, p);
			if (_gravity)
				_registry->addGeneratorToParticle(_gravity, p);
			


		}

	}

	
	//me recorro las particulas para ver la sque tengo que eliminar
	auto it = _particles.begin();
	while (it != _particles.end()) {
		Particle* p = *it;

		if (!p->isAlive()) {
			delete p;
			it = _particles.erase(it);
		}
		else {
			p->integrate(t);
			++it;
		}
	}



}

void ParticleSystem::addGenerator(ParticleGen* g)
{
	_generators.push_back(g);
}



