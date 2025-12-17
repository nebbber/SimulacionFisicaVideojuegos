#pragma once
#include <PxPhysicsAPI.h> 
#include <vector>

class ForceRegistry;
class Whirlwind;
class Gravity;
class OscillateWind;

class SolidSystem {
protected:
    bool active = false;
    std::vector<physx::PxRigidActor*> bodies;
    ForceRegistry* _registry = nullptr;

    Gravity* _gravity = nullptr;
    OscillateWind* _oscillate = nullptr;

public:
    SolidSystem();
    ~SolidSystem();

    virtual void update(double t) {};
    void ActivateSolid(bool a);

    bool isActive();
    void ActivateGravity(bool a);
    void ActivateOscilate(bool a);
};