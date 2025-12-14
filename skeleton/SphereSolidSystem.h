#pragma once
#include "SolidSystem.h"
#include "PxPhysicsAPI.h"
#include "Gravity.h"
#include "Whirlwind.h" 
#include "GaussianSolidGen.h"
#include "OscillateWind.h"
#include <vector>
class SphereSolidSystem : public SolidSystem
{
private:

	GaussianSolidGen* sphere;

	PxMaterial* defaultMat;
	PxScene* scene;
	vector<RenderItem*>renderItems;

public:
	SphereSolidSystem(PxPhysics* p, PxScene* s, Gravity* g, OscillateWind* w,PxVec3 pos);
	void removeDeadBodies();
	void update(double t) override;
	~SphereSolidSystem();
	void DeregisterRenderItems(PxRigidActor* actor);
	Vector4 randomColor();
};

