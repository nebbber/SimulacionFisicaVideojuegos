#pragma once
#include "WindGenerator.h"
#include "PxPhysicsAPI.h"

class Whirlwind: public WindGenerator
{
private:
	Vector3 posCentro;
	float K;
	Vector3 velViento;
public:
	Whirlwind(float _K, Vector3 _posCentro, Vector3 vel, float k1, float k2);
	~Whirlwind();
	void update(double t, Particle* p) override;
	void update(double t, PxRigidDynamic* r) override;
};

