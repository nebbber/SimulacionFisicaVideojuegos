#pragma once
#include "ParticleSystem.h"
class Gravity;
class OscillateWind;
class GaussianGen;
class SparkleSystem: public ParticleSystem
{
private:

	GaussianGen* spark;

public:
	 SparkleSystem(Gravity* g, WindGenerator* w, OscillateWind* o);

	 void update(double t) override;
	 ~SparkleSystem();

};

