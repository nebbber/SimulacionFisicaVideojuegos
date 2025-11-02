#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGen.h"
#include "GaussianGen.h"
class ForceRegistry;
class Gravity;
class WindGenerator;
class Whirlwind;
class ParticleSystem
{
private:
	std::list<Particle*> _particles;
	std::list<Particle*> nuevasParticulas;
	std::list<ParticleGen*> _generators;
	ForceRegistry* _registry;  
	Gravity* _gravity = nullptr; 
	WindGenerator* _wind = nullptr;
	Whirlwind* _whril = nullptr;
public:
	ParticleSystem(ForceRegistry* _registry);
	void update(double t);// te recorres todas y cunado sea no alive la borras
	void addGenerator(ParticleGen* g);
	~ParticleSystem();
	void setGravity(Gravity* g);
	void setWind(WindGenerator* w);
	void setWhril(Whirlwind* ww);
};

