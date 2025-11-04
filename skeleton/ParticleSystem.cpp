#include "ParticleSystem.h"
#include "Gravity.h"
#include "ForceRegistry.h"
#include "WindGenerator.h"
#include "Whirlwind.h"
#include "OscillateWind.h"
#include "ForceGenerator.h"
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
	delete _oscillate;
}
void ParticleSystem::setGravity(Gravity* g)
{
	//if (_gravity) delete _gravity;
	_gravity = g;
}

void ParticleSystem::setWind(WindGenerator* w)
{
	//if (_wind) delete _wind;
	_wind = w;
}

void ParticleSystem::setWhril(Whirlwind* ww)
{
	//if (_whril) delete _whril;
	_whril = ww;
}

void ParticleSystem::setOscillate(OscillateWind* o)
{
	//if (_oscillate) delete _oscillate;
	_oscillate = o;
}




void ParticleSystem::update(double t)
{

	for (ParticleGen* gen : _generators)
	{
		auto generatedParticles = gen->generateP();
		std::string groupName = gen->getName();  // ej: "fuente", "fuego", "nieve"

		for (Particle* p : generatedParticles)
		{
			p->setGeometry();
			_particles.push_back(p);

			// Registro selectivo de fuerzas según el grupo
			if (groupName == "fuente") {
				if (_gravity) _registry->addGeneratorToParticle(this, groupName, _gravity, p);
				//if (_wind)     _registry->addGeneratorToParticle(this, groupName, _wind, p);
			}
			else if (groupName == "fuego") {
				if (_gravity)  _registry->addGeneratorToParticle(this, groupName, _gravity, p);
			}
			else if (groupName == "nieve") {
				if (_gravity)  _registry->addGeneratorToParticle(this, groupName, _gravity, p);
			}
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



