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

void ParticleSystem::setOscillate(OscillateWind* o)
{
	if (_oscillate) delete _oscillate;
	_oscillate = o;
}

void ParticleSystem::update(double t)
{
    // Generar nuevas partículas
    for (ParticleGen* gen : _generators)
    {
        auto generatedParticles = gen->generateP();
        std::string groupName = gen->getName();

        for (Particle* p : generatedParticles)
        {
            p->setGeometry();
            _particles.push_back(p);
        }
            
        
    }

    // Actualizar fuerzas de todas las partículas registradas
    _registry->updateForces(t);

    // Integrar partículas y eliminar las muertas
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


