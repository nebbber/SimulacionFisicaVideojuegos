#pragma once
#include <PxPhysicsAPI.h>
#include <vector>
using namespace physx;

class SolidGenerator {
protected:
    PxPhysics* physics;
    PxScene* scene;
    PxMaterial* defaultMat;
    bool isActive = false;

public:
    SolidGenerator(PxPhysics* p, PxScene* s, PxMaterial* mat)
        : physics(p), scene(s), defaultMat(mat) {
    }

    virtual ~SolidGenerator() {}

    void setActive(bool a) { isActive = a; }
    bool getActive() const { return isActive; }
    virtual std::vector<PxRigidDynamic*> generateRigidBodies() = 0;
};