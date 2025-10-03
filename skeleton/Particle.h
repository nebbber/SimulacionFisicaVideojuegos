#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"
#include <vector>
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
	float gravedad;
public:
	Particle(Vector3 Pos, Vector3 VelS, Vector3 VelR, Vector3 Acc, float d, float mS, float mR, float g);
	~Particle();

	void integrate(double t);
	void semi(double t);
	void verlet(double t);
	//metoddo euler semi implicito 

};

