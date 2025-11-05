#pragma once
#include "ParticleGen.h"
#include "Particle.h"
#include <random>
#include <list>
class UniformGen :public ParticleGen
{
private:

	std::uniform_real_distribution<double> _r;
	list<Particle*> particles;

	Vector3 desvP;//cuanto de esparcido
	Vector3 desvV;
	double desvD;
	double time;
	bool isActive = false;
public:
	UniformGen(std::string nam);
	~UniformGen();
	void setDesP(Vector3 p);
	void setDesV(Vector3 v);
	list<Particle*> generateP() override;
	std::list<Particle*> getParticles() const;
};