#pragma once
#include "BaseScene.h"
#include "callbacks.hpp"
#include "RenderUtils.hpp"

class Gravity;
class WindGenerator;
class OscillateWind;
class ParticleSystem;
class BulletSystem;
class SnowSystem;
class SparkleSystem;
class ScenePractica : public BaseScene {
private:
    // physX
    PxDefaultCpuDispatcher* gDispatcher = nullptr;
    ContactReportCallback gContactReportCallback;

    // dianas
    RenderItem* itemX = nullptr;
    RenderItem* itemY = nullptr;
    RenderItem* itemZ = nullptr;

    // fuerzas y el registro
    Gravity* gravity = nullptr;
    WindGenerator* wind = nullptr;
    OscillateWind* oscillate = nullptr;

    // particulas 
    ParticleSystem* particleSystem = nullptr;
    // generadores
    bool pressedNieve = false;
    physx::PxVec3 posGanar;
    SparkleSystem* sparSys;
    SnowSystem* snowSys;
    BulletSystem* bulletSys;

    //booleanos para activacion/desactivacion de generadores de fuerzas
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