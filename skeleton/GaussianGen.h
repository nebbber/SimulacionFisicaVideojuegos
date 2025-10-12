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

public:
	list<Particle*> generateP() override;


};

