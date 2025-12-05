#pragma once
#include "SolidSystem.h"
#include "PxPhysicsAPI.h"
class Gravity;
class GaussianSolidGen;
class CubeSolidSystem : public SolidSystem
{
private:

	GaussianSolidGen* cube;
	PxMaterial* defaultMat;

public:
	CubeSolidSystem(PxPhysics* p, PxScene* s, Gravity* g);

	void update(double t) override;
	~CubeSolidSystem();

};

