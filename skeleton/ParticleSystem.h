#pragma once
#include <list>
#include "Particle.h"
#include <map>
class ForceRegistry;
class Gravity;
class WindGenerator;
class Whirlwind;
class OscillateWind;
class ForceGenerator;
class ParticleGen;
class SpringForceGenerator;
class FloatForce;
class Whirlwind;
class ParticleSystem
{
protected:
	std::list<Particle*> _particles;
	std::list<Particle*> nuevasParticulas;
	std::list<ParticleGen*> _generators;
	ForceRegistry* _registry = nullptr;
	Gravity* _gravity = nullptr;
	WindGenerator* _wind = nullptr;
	OscillateWind* _oscillate = nullptr;
	bool active = true;

	SpringForceGenerator* _spring1 = nullptr;
	SpringForceGenerator* _spring2 = nullptr;
	SpringForceGenerator* _spring3 = nullptr;
	Whirlwind* _whril = nullptr;

	FloatForce* _float = nullptr;
public:
	ParticleSystem();
	virtual void update(double t) {};
	~ParticleSystem();
	void ActivateParticle(bool a);

	void ActivateGravity(bool a);
	void ActivateOscilate(bool a);
	void ActivateWind(bool a);
	void ActivateSpring(bool a);
	void ActivateFloat(bool a);
	void ActivateWhril(bool a);


	bool isActive();


};

