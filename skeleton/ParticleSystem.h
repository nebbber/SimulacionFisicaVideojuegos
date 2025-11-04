#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGen.h"
#include "GaussianGen.h"
#include <map>
class ForceRegistry;
class Gravity;
class WindGenerator;
class Whirlwind;
class OscillateWind;
class ForceGenerator;
class ParticleSystem
{
protected:
	std::list<Particle*> _particles;
	std::list<Particle*> nuevasParticulas;
	std::list<ParticleGen*> _generators;
	ForceRegistry* _registry;  
	std::string name;
	Gravity* _gravity = nullptr;
	WindGenerator* _wind = nullptr;
	Whirlwind* _whril = nullptr;
	OscillateWind* _oscillate = nullptr;
	std::map<std::string, std::vector<ForceGenerator*>> _groupForces;
public:
	ParticleSystem(ForceRegistry* _registry);
	void update(double t);// te recorres todas y cunado sea no alive la borras
	void addGenerator(ParticleGen* g);
	~ParticleSystem();
	void setActiveGen(std::string name, bool active);

	void setGravity(Gravity* g);
	void setWind(WindGenerator* w);
	void setWhril(Whirlwind* ww);
	void setOscillate(OscillateWind* o);
	void addForceToGroup(const std::string& groupName, ForceGenerator* fg);
};

