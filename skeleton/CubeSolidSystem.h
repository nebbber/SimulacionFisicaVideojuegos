#pragma once
#include "SolidSystem.h"
#include "PxPhysicsAPI.h"
#include "Gravity.h"
#include "Whirlwind.h" 
#include "GaussianSolidGen.h"
#include "OscillateWind.h"
#include <vector>
class CubeSolidSystem : public SolidSystem
{
private:

	GaussianSolidGen* cube;

	PxMaterial* defaultMat;
	PxScene* scene;
	vector<RenderItem*>renderItems;

public:
	CubeSolidSystem(PxPhysics* p, PxScene* s, Gravity* g, OscillateWind* w, PxVec3 pos);
	void removeDeadBodies();
	void update(double t) override;
	~CubeSolidSystem();
	void DeregisterRenderItems(PxRigidActor* actor);
	Vector4 randomColor();
};

