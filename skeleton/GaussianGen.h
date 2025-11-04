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
	list<Particle*> particles;

	Vector3 desvP;//cuanto de esparcido
	Vector3 desvV;
	double desvD;
	double time;
	Particle* modelo;
public:
	GaussianGen(std::string nam);
	~GaussianGen();
	void setDesP(Vector3 p);
	 void setDesV(Vector3 v);
	list<Particle*> generateP() override;


};

