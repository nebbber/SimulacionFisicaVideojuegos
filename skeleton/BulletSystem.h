#pragma once
#include "Particle.h"
#include "Vector3D.h"
#include "Gravity.h"
#include "ForceRegistry.h"
#include "OscillateWind.h"
#include <vector>
#include <iostream>
#include "ParticleSystem.h"
class BulletSystem:public ParticleSystem
{
private:
    std::vector<Particle*> bullets;
    ForceRegistry* _registry;
    bool active = true;

public:
    BulletSystem(Gravity* g, WindGenerator* w, OscillateWind* o);
    ~BulletSystem();

    void createBullet(Vector3 pos, double velS, Vector3 velR, Vector3 acc, float damping, float massR, PxVec3 dir, Vector4 color);
    bool isEmpty() const;
    void shot(double t);
    std::vector<Particle*> getBullets() const;
    void deactivate() { active = false; }
    bool isActive() const { return active; }
};