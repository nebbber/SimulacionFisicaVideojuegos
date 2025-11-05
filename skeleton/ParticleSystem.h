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
	ForceRegistry* _registry = nullptr;
	Gravity* _gravity = nullptr;
	WindGenerator* _wind = nullptr;
	//Whirlwind* _whril = nullptr;
	OscillateWind* _oscillate = nullptr;
	bool active = false;
public:
	ParticleSystem();
	virtual void update(double t) {};// te recorres todas y cunado sea no alive la borras
	~ParticleSystem();
	void ActivateParticle(bool a); //para deascituvar particulas 

	//y 3 para descativar generadores 
	void ActivateGravity(bool a);
	void ActivateOscilate(bool a);
	void ActivateWind(bool a);
	
	
};

