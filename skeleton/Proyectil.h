#pragma once
#include "Particle.h"
#include <vector>
using namespace std;
using namespace physx;
class Proyectil
{
private:
	vector<Particle*> bullets;
	bool empty;
public:
	Proyectil();
	void createBullet(Vector3 Pos, double VelS, Vector3 VelR, Vector3 Acc, float d, float mR, PxVec3 dir, Vector4 color);
	bool isEmpty();
	void shot(double t);
	~Proyectil();
};

