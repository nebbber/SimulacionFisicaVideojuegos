#pragma once
#include "Particle.h"
#include <vector>
using namespace std;
using namespace physx;
class Proyectil
{
private:
	vector<Particle> particulas;
	
public:
	Proyectil();
	void shoot(Vector3 Pos, Vector3 VelS, Vector3 VelR, Vector3 Acc, float d, float mR, float g, PxVec3 dir);

};

