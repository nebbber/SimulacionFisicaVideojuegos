#pragma once
#include <PxPhysicsAPI.h>
#include <vector>
#include "Gravity.h"
#include "ForceRegistry.h"
using namespace physx;
class SolidSystem {
   protected:
    bool active = false;

    std::vector<PxRigidActor*> bodies;
    ForceRegistry* _registry = nullptr;

    Gravity* _gravity = nullptr;
public:


    SolidSystem();
    ~SolidSystem();

    virtual void update(double t) {};
    void ActivateSolid(bool a);
};