#pragma once
#include "ForceGenerator.h"
class Gravity: public ForceGenerator
{
private:
	Vector3 gravity;
public:
	Gravity(Vector3 g);
	~Gravity();
	void update(double t, Particle* p) override;
};

