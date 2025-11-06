#include "ScenePractica.h"
#include "Vector3D.h"
#include "core.hpp"
#include <iostream>
#include "foundation/PxTransform.h"
#include "SparkleSystem.h"
#include "BulletSystem.h"
#include "ParticleSystem.h"
#include "ForceRegistry.h"
#include "Gravity.h"
#include "WindGenerator.h"
#include "Whirlwind.h"
#include "UniformGen.h"
#include "GaussianGen.h"
#include "OscillateWind.h"
#include "SnowSystem.h"
using namespace physx;
ScenePractica::ScenePractica(PxPhysics* physics) : BaseScene(physics) {}

ScenePractica::~ScenePractica() {}

void ScenePractica::init() {

    // === Crear escena PhysX ===
    PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
    sceneDesc.gravity = PxVec3(0.0f, -40.8f, 0.0f);
    gDispatcher = PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = gDispatcher;
    sceneDesc.filterShader = contactReportFilterShader;
    sceneDesc.simulationEventCallback = &gContactReportCallback;
    gScene = gPhysics->createScene(sceneDesc);

    gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
 
    // === Dianas ===
    PxSphereGeometry geo(5.0f); //antes para ejes 2
    PxShape* shape = CreateShape(geo, gMaterial);
    
    itemX = new RenderItem(shape, new PxTransform(Vector3(50, 40, -80)), Vector4(0, 1, 0, 1));
    itemY = new RenderItem(shape, new PxTransform(Vector3(00, 0, -80)), Vector4(0, 1, 0, 1));
    itemZ = new RenderItem(shape, new PxTransform(Vector3(-50, -20, -80)), Vector4(0, 1, 0, 1));


    //ejes antiguos
   /* itemX = new RenderItem(shape, new PxTransform(PxVec3(10, 0, 0)), Vector4(1, 0, 0, 1));
    itemY = new RenderItem(shape, new PxTransform(PxVec3(0, 10, 0)), Vector4(0, 1, 0, 1));
    itemZ = new RenderItem(shape, new PxTransform(PxVec3(0, 0, 10)), Vector4(0, 0, 1, 1));
    */
    RegisterRenderItem(itemX);
    RegisterRenderItem(itemY);
    RegisterRenderItem(itemZ);

    // === Fuerzas ===
    gravity = new Gravity(Vector3(0, -90.8f, 0));
    wind = new WindGenerator(Vector3(0.0f, 0.0f, 20000.0f), 0.3f, 0.0f);
    oscillate = new OscillateWind(Vector3(0.0f, 100.0f, 0.0f), 0.5f, 0.1f, 300.0f, 3.0f);

    // === Proyectiles y partículas ===
    particleSystem = new ParticleSystem();
    sparSys = new SparkleSystem(gravity,nullptr, oscillate);
    snowSys = new SnowSystem(gravity,wind,nullptr);
    bulletSys = new BulletSystem(nullptr,nullptr,nullptr);
   
    // antigua fuente sin adapatr a sistema de particulas
    /*fuente = new UniformGen("fuente");

    // Modelo fuente
    Particle* modeloFuente = new Particle(7.0, Vector3(0, 40, -80), Vector3(0, 0, 0),
        Vector3(0, 0, 0), 0.4f, 20.0f, Vector4(0, 1, 1, 1), 0.02f);
    fuente->setModelo(modeloFuente);
    fuente->setNumParticles(5);
    fuente->setDurMedia(1.0);
    fuente->setPosMedia(Vector3(25.0f, 0.0f, 0.0f));
    fuente->setVelMedia(Vector3(0.0f, 40.0f, 0.0f));
    fuente->setDesP(Vector3(1, 0, 1));
    fuente->setDesV(Vector3(10, 10, 10));
    fuente->setProbGen(0.2);
    */
   
 
}

void ScenePractica::step( double t) //ES EL UPDATE
{
    static bool primeraVez = true;

    //cogemos la pos inicial de la camara 
    if (primeraVez) {
        Camera* cam = GetCamera();
        if (cam) {
            posGanar = cam->getTransform().p;
            primeraVez = false;
        }
    }
  
    //PX_UNUSED(interactive);
    if (!bulletSys->isEmpty())
    {
        //llamar al integrate de cada bala

        bulletSys->shot(t);
    }
    sparSys->update(t);
    snowSys->update(t);
    gScene->simulate(t);
    gScene->fetchResults(true);

    Camera* cam = GetCamera();

    //aparece "nieve" delimitadora de espacio de disparo
    if (cam->getTransform().p.magnitude() > 130.0)
    {
        snowSys->ActivateParticle(true);
    }
    else 
    {
        snowSys->ActivateParticle(false);
    }
}

void ScenePractica::onKeyPress(unsigned char key, const PxTransform& camera) {

    switch (toupper(key))
    {
        //case 'B': break;
        //case ' ':	break;
    case ' ':
    {
        break;
    }
    case 'P':
    {
        //bala de cañon
        Camera* cam = GetCamera();
        Vector4 color(1, 1, 0, 1);
        //la pos de la camara como pos inicial de la particula

        bulletSys->createBullet(cam->getTransform().p, 200.0, Vector3(0.0f, 1000.0f, 0.0f),
            Vector3(0.0f, -9.8f, 0.0f), 0.4f, 4.0f, cam->getDir(), color);

        break;
    }
    /*case 'O':
    {
        //bala de tanque

        Camera* cam = GetCamera();
        Vector4 color(0, 1, 0, 1);

        //la pos de la camara como pos inicial de la particula
        proyectil->createBullet(cam->getTransform().p, 100.0, Vector3(0.0f, 1800.0f, 0.0f),
            Vector3(0.0f, -9.8f, 0.0f), 0.4f, 4.0f, cam->getDir(), color);
        break;
    }*/
    case 'I':
    {
        //bala de pistola

        Camera* cam = GetCamera();
        Vector4 color(0, 1, 1, 1);
        bulletSys->createBullet(cam->getTransform().p, 400.0, Vector3(0.0f, 330.0f, 0.0f),
            Vector3(0.0f, -9.8f, 0.0f), 0.4f, 2.6f, cam->getDir(), color);
   
        break;
    }
    case 'M':
    {
        Camera* cam = GetCamera();
        cam->setTransform(posGanar);
        showSparkle = !showSparkle;
        sparSys->ActivateParticle(showSparkle);
      
      
        break;
    }

    case 'Y':
    {
        boolGravity = !boolGravity;
        sparSys->ActivateGravity(boolGravity);
        snowSys->ActivateGravity(boolGravity);
        break;
    }
    case 'T':
    {
        boolWind = !boolWind;
        snowSys->ActivateWind(boolWind);
        break;
    }
    case 'R':
    {
        boolOscilate = !boolOscilate;
        sparSys->ActivateOscilate(boolOscilate);
        break;
    }
    default:
        break;
    }
    
}
void ScenePractica::Win()
{


}
void ScenePractica::cleanup() {
    DeregisterRenderItem(itemX);
    DeregisterRenderItem(itemY);
    DeregisterRenderItem(itemZ);
    delete itemX; delete itemY; delete itemZ;

    if (gScene) gScene->release();
    if (gDispatcher) gDispatcher->release();
    if (gMaterial) gMaterial->release();

    delete gravity;
    delete wind;
    delete oscillate;
}