#pragma once
#include <PxPhysicsAPI.h>

using namespace physx;

class BaseScene {
protected:
    PxPhysics* gPhysics = nullptr;
    PxScene* gScene = nullptr;
    PxMaterial* gMaterial = nullptr;

public:
    BaseScene() {};
    virtual ~BaseScene() {}

    virtual void init() = 0;
    virtual void step(double t) = 0;
    virtual void cleanup() = 0;
    virtual void onKeyPress(unsigned char key, const PxTransform& camera) { PX_UNUSED(camera); 	PX_UNUSED(key);
    }
    virtual void onCollision(PxActor* actor1, PxActor* actor2) {
    }
    PxScene* getScene() const { return gScene; }
};