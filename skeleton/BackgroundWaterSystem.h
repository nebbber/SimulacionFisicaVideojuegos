#pragma once
#include "ParticleSystem.h"
class Gravity;
class OscillateWind;
class GaussianGen;
class BackgroundWaterSystem : public ParticleSystem
{
private:

	GaussianGen* p;

public:
	BackgroundWaterSystem(Gravity* g, WindGenerator* w, OscillateWind* o);

	 void update(double t) override;
	 ~BackgroundWaterSystem();

};

