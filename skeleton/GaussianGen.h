#pragma once
#include "ParticleGen.h"
#include "Particle.h"
#include <random>
#include <list>
class GaussianGen:public ParticleGen
{
private:

	std::normal_distribution <double> _d; //prob de duracion pos, vel ...  y para la prob de generar particula es
	//la uniforme
	int n_particles;
	list<Particle*> particles;
	Vector3 posMedia;
	Vector3 velMedia;
	double durMedia;
	Vector3 desvP;//cuanto de esparcido
	Vector3 desvV;
	double desvD;
	Particle* modelo;
	double time;

public:
	GaussianGen();
	list<Particle*> generateP() override;


};

