#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"
#include <vector>

using namespace std;
using namespace physx;
class Particle
{
private:
	Vector3 velR;
	Vector3 velS;
	float masaR;
	float masaS;
	Vector3 acc;
	physx::PxTransform* pose; // A render item le pasaremos la direccion de este pose, para que se actualice automaticamente
	RenderItem* renderItem;
	Vector3 initialPose;
	float dumping;
	bool alive;
	double time;
public:
	Particle(double time,Vector3 Pos, Vector3 VelS, Vector3 VelR, Vector3 Acc, float d, float mS, float mR, Vector4 color);
	~Particle();

	void integrate(double t);
	void semi(double t);
	void verlet(double t);
	bool isAlive();

};

