#include "ParticleSystem.h"
#include <iostream>
using namespace std;

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



