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
#include "OscillateWind.h"
#include "SnowSystem.h"

class BulletSystem;
class  SparkleSystem;
class ScenePractica : public BaseScene {
private:
    // physX
    PxDefaultCpuDispatcher* gDispatcher = nullptr;
    ContactReportCallback gContactReportCallback;

    // ejes
    RenderItem* itemX = nullptr;
    RenderItem* itemY = nullptr;
    RenderItem* itemZ = nullptr;

    // fuerzas y el registro
    Gravity* gravity = nullptr;
    Gravity* softGravity = nullptr;
    WindGenerator* wind = nullptr;
    Whirlwind* whirl = nullptr;
    ForceRegistry* registry = nullptr;
    OscillateWind* oscillate = nullptr;

    // particulas y proyectiles
    ParticleSystem* particleSystem = nullptr;
    Proyectil* proyectil = nullptr;

    // generadores
    UniformGen* fuente = nullptr;
    GaussianGen* fuego = nullptr;
    GaussianGen* nieve = nullptr;
    bool pressedNieve = false;
    physx::PxVec3 posGanar;
    SparkleSystem* sparSys;
    SnowSystem* snowSys;
    BulletSystem* bulletSys;

    bool boolGravity=true;
    bool boolWind = true;
    bool showSparkle = false;
    bool boolOscilate = true;


public:
    ScenePractica(PxPhysics* physics);
    ~ScenePractica() override;

    void init() override;
    void step(double t) override;
    void cleanup() override;
    void onKeyPress(unsigned char key, const PxTransform& camera) override;
    void Win();
};