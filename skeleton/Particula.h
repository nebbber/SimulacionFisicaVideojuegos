#pragma once
#include "RenderUtils.hpp"
#include "core.hpp"
#include <vector>
class Particula
{
private:
	Vector3 vel;
	physx::PxTransform pose; // A render item le pasaremos la direccion de este pose, para que se actualice automaticamente
	RenderItem* renderItem;

public:
	Particula(Vector3 Pos, Vector3 Vel);
	~Particula();

	void integrate(double t);


};

