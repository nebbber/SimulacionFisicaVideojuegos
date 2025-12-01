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
class Particle;
class ForceRegistry;
class SpringForceGenerator;
class MuellePracticaSystem;
class FlotacionPracticaSystem;
class FloatForce;
class FontainSystem;
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


    SpringForceGenerator* spring1 = nullptr;
    SpringForceGenerator* spring2 = nullptr;
    SpringForceGenerator* spring3 = nullptr;

    FloatForce* floatP = nullptr;

    // particulas 
    ParticleSystem* particleSystem = nullptr;
    // generadores
    bool pressedNieve = false;
    physx::PxVec3 posGanar;
    SparkleSystem* sparSys;
    SnowSystem* snowSys;
    BulletSystem* bulletSys;
    MuellePracticaSystem* muelleSys;
    FlotacionPracticaSystem* floatSys;
    FontainSystem* fuenteSys;

    //booleanos para activacion/desactivacion de generadores de fuerzas
    bool boolGravity=true;
    bool boolWind = true;
    bool showSparkle = false;
    bool boolOscilate = true;
    bool boolSpring1 = true;
    bool boolSpring2 = true;

    //crear solidos rígidos
    PxFoundation* gFoundation = nullptr;
    PxPvd* gPvd;//debuggear

public:
    ScenePractica();
    ~ScenePractica() override;

    void init() override;
    void step(double t) override;
    void cleanup() override;
    void onKeyPress(unsigned char key, const PxTransform& camera) override;
    void Win();
};