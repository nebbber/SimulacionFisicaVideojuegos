#pragma once
#include <PxPhysicsAPI.h>
#include <vector>

class SolidGenerator {
protected:
    physx::PxPhysics* physics;
    physx::PxScene* scene;
    physx::PxMaterial* defaultMat;
    bool isActive;

public:
    SolidGenerator(physx::PxPhysics* p, physx::PxScene* s, physx::PxMaterial* mat)
        : physics(p), scene(s), defaultMat(mat), isActive(false) {
    }

    virtual ~SolidGenerator() {}

    void setActive(bool a) { isActive = a; }
    bool getActive() const { return isActive; }

    virtual std::vector<physx::PxRigidDynamic*> generateRigidBodies() = 0;
};