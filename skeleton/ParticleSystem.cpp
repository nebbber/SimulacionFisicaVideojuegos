#include "ParticleSystem.h"
#include <iostream>
using namespace std;

ParticleSystem::ParticleSystem()
{
	pg = new GaussianGen();
	_generators.push_back(pg);
	
	for (ParticleGen* gen : _generators)
	{
		auto g = gen->generateP();

		for (Particle* p : g)
		{
			_particles.push_back(p);
		}

	}
}

ParticleSystem::~ParticleSystem()
{
	delete pg;

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
	//me recorro las particulas para ver la sque tengo que eliminar
	for (auto it = _particles.begin(); it != _particles.end(); )
	{
		if (!(*it)->isAlive())
		{
			//std::cout << "muerta?" << endl;
			delete* it;            // liberamos memoria
			it = _particles.erase(it); // borramos puntero de la lista y avanzamos iterador
		}
		else
		{
			++it;
		}
	}
	//me recorro los generadores y me saco las lista de partuclas que tenga
	//luego me paso los de esa lista a la lista de particulas

	
	//integro las particulas
	for (Particle* p : _particles)
	{
		p->integrate(t);
	}



}



