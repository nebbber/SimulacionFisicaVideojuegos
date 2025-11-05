#pragma once
#include "Particle.h"
#include "Vector3D.h"
#include "Gravity.h"
#include "ForceRegistry.h"
#include "OscillateWind.h"
#include <vector>
#include <iostream>

class BulletSystem
{
private:
    std::vector<Particle*> bullets;
    Gravity* _gravity;
    OscillateWind* _oscillate;
    ForceRegistry* _registry;

public:
    // Constructor y destructor
    BulletSystem(Gravity* g, OscillateWind*);
    ~BulletSystem();

    // Métodos
    void createBullet(Vector3 pos, double velS, Vector3 velR, Vector3 acc, float damping, float massR, PxVec3 dir, Vector4 color);
    bool isEmpty() const;
    void shot(double t);
    std::vector<Particle*> getBullets() const;
};