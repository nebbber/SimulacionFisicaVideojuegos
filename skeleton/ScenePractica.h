#pragma once
#include "BaseScene.h"
#include "callbacks.hpp"
#include "RenderUtils.hpp"
#include "ParticleSystem.h"
#include "Proyectil.h"
#include "ForceRegistry.h"
#include "Gravity.h"
#include "WindGenerator.h"
#include "Whirlwind.h"
#include "UniformGen.h"
#include "GaussianGen.h"

class ScenePractica : public BaseScene {
private:
    // Elementos PhysX
    PxDefaultCpuDispatcher* gDispatcher = nullptr;
    ContactReportCallback gContactReportCallback;

    // Render items
    RenderItem* itemX = nullptr;
    RenderItem* itemY = nullptr;
    RenderItem* itemZ = nullptr;

    // Fuerzas y sistemas
    Gravity* gravity = nullptr;
    Gravity* softGravity = nullptr;
    WindGenerator* wind = nullptr;
    Whirlwind* whirl = nullptr;
    ForceRegistry* registry = nullptr;

    // Partículas y proyectiles
    ParticleSystem* particleSystem = nullptr;
    Proyectil* proyectil = nullptr;

    // Generadores
    UniformGen* fuente = nullptr;
    GaussianGen* fuego = nullptr;
    GaussianGen* nieve = nullptr;

public:
    ScenePractica(PxPhysics* physics);
    ~ScenePractica() override;

    void init() override;
    void step(double t) override;
    void cleanup() override;
    void onKeyPress(unsigned char key, const PxTransform& camera) override;

};