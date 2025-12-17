#pragma once
#include "ParticleSystem.h"
class Gravity;
class OscillateWind;
class GaussianGen;
class BreathWater : public ParticleSystem
{
private:

	GaussianGen* p;
	bool emitting = true;
public:
	BreathWater(Gravity* g, Whirlwind* w);

	void update(double t) override;
	~BreathWater();
	void setPosition(const Vector3& pos);
	void stopEmission();

};

