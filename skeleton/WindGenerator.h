#pragma once
#include "ForceGenerator.h"
class WindGenerator:public ForceGenerator
{ 
	private:
		Vector3 velViento;
		float k1;
		float k2;

	public:
	WindGenerator(Vector3 vel,float ks, float k);
	~WindGenerator();
	void update(double t, Particle* p) override;

};

