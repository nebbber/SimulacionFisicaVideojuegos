#pragma once
#include "ParticleSystem.h"
class Gravity;
class SparkleSystem: public ParticleSystem
{
private:

	GaussianGen* spark;

public:
	 SparkleSystem(Gravity* g);

	 void update(double t) override;
	 ~SparkleSystem();

	 void addForceGenerator(ForceGenerator* fg);
};

