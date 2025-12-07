#pragma once
#include "ParticleSystem.h"
class Gravity;
class OscillateWind;
class GaussianGen;
class FontainSystem : public ParticleSystem
{
private:

	GaussianGen* fuente;

public:
	FontainSystem(Gravity* g, Whirlwind* w);

	void update(double t) override;
	~FontainSystem();
	void setPosition(const Vector3& pos);


};

