#pragma once
#include <random>
#include "core.hpp"
#include "Particle.h"
#include <list>
class ParticleGen
{
private:
	

protected:
	std::mt19937 _mt;
	std::uniform_real_distribution<double> _u; //de 0 a 1 porb de generar particula lo tienen todas en la uniforme utiliza
	//tambien esta para la vel, pos...
	Vector3 pos;
	Vector3 vel;
	double dur;
	double probGen;

public:
	virtual list<Particle*> generateP() = 0;
	void setPos( Vector3 p);
	void setVel(Vector3 v);
	void setDur(double d); //duracion
	void setProbGen(double pg);//probabilidad de generacion

	Vector3 getPos();
	Vector3 getVel();
	double getDur();
	double getProbGen();

};