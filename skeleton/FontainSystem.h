#pragma once
#include "ParticleSystem.h"
class Gravity;
class OscillateWind;
class UniformGen;
class FontainSystem : public ParticleSystem
{
private:

	UniformGen* fuente;

public:
	FontainSystem(Gravity* g);

	void update(double t) override;
	~FontainSystem();

	
};

