#include "ScenePractica.h"
#include "Vector3D.h"
#include "core.hpp"
#include <iostream>

ScenePractica::ScenePractica(PxPhysics* physics) : BaseScene(physics) {}

ScenePractica::~ScenePractica() {}

void ScenePractica::init() {
    std::cout << "Inicializando escena práctica..." << std::endl;

    // === Crear escena PhysX ===
    PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
    sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
    gDispatcher = PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = gDispatcher;
    sceneDesc.filterShader = contactReportFilterShader;
    sceneDesc.simulationEventCallback = &gContactReportCallback;
    gScene = gPhysics->createScene(sceneDesc);

    gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
 
    // === Ejes ===
    PxSphereGeometry geo(2.0f);
    PxShape* shape = CreateShape(geo, gMaterial);
    

    itemX = new RenderItem(shape, new PxTransform(PxVec3(10, 0, 0)), Vector4(1, 0, 0, 1));
    itemY = new RenderItem(shape, new PxTransform(PxVec3(0, 10, 0)), Vector4(0, 1, 0, 1));
    itemZ = new RenderItem(shape, new PxTransform(PxVec3(0, 0, 10)), Vector4(0, 0, 1, 1));

    RegisterRenderItem(itemX);
    RegisterRenderItem(itemY);
    RegisterRenderItem(itemZ);

    // === Fuerzas ===
    gravity = new Gravity(Vector3(0, -9.8f, 0));
    softGravity = new Gravity(Vector3(0, -2.8f, 0));
   // wind = new WindGenerator(Vector3(0.0f, 0.0f, 500.0f), 0.5f, 0.0f);
   // whirl = nullptr; 
   // oscillate = new OscillateWind(Vector3(0.0f, 50.0f, .0f), 0.5f, 0.1f, 10.0f, 0.5f);

    registry = new ForceRegistry();

    // === Proyectiles y partículas ===
    proyectil = new Proyectil();
    particleSystem = new ParticleSystem(registry);
    particleSystem->setGravity(gravity);
   // particleSystem->setWind(wind);
    
    //particleSystem->setOscillate(oscillate);
    //particleSystem->setWhril(whirl);

    // === Generadores ===
    fuente = new UniformGen();
    fuego = new GaussianGen();
    nieve = new GaussianGen();

    // Modelo fuente
    Particle* modeloFuente = new Particle(7.0, Vector3(0, 0, 0), Vector3(0, 0, 0),
        Vector3(0, 0, 0), 0.4f, 20.0f, Vector4(0, 1, 1, 1), 0.02f);
    fuente->setModelo(modeloFuente);
    fuente->setNumParticles(5);
    fuente->setDurMedia(1.0);
    fuente->setPosMedia(Vector3(25.0f, 0.0f, 0.0f));
    fuente->setVelMedia(Vector3(0.0f, 40.0f, 0.0f));
    fuente->setDesP(Vector3(1, 0, 1));
    fuente->setDesV(Vector3(10, 10, 10));
    fuente->setProbGen(0.2);
    particleSystem->addGenerator(fuente);

    // Modelo fuego
    Particle* modeloFuego = new Particle(7.0, Vector3(0, 0, 0), Vector3(0, 0, 0),
        Vector3(0, 0, 0), 0.4f, 20.0f, Vector4(1, 0, 0, 1), 0.2f);
    fuego->setModelo(modeloFuego);
    fuego->setNumParticles(20);
    fuego->setDurMedia(1.0);
    fuego->setPosMedia(Vector3(-25.0f, 0.0f, 0.0f));
    fuego->setVelMedia(Vector3(10.0f, 10.0f, 10.0f));
    fuego->setDesP(Vector3(0.4f, 0, 0.4f));
    fuego->setDesV(Vector3(20, 20, 20));
    fuego->setProbGen(0.2);
    particleSystem->addGenerator(fuego);

    // Modelo nieve
    Particle* modeloNieve = new Particle(7.0, Vector3(0, 0, 0), Vector3(0, 0, 0),
        Vector3(0, 0, 0), 0.4f, 40.0f, Vector4(1, 1, 1, 1), 0.2f);
    nieve->setModelo(modeloNieve);
    nieve->setNumParticles(5);
    nieve->setDurMedia(0.2);
    nieve->setPosMedia(Vector3(0, 0, 0));
    nieve->setVelMedia(Vector3(1, 1, 1));
    nieve->setDesP(Vector3(20, 20, 20));
    nieve->setDesV(Vector3(5, 5, 5));
    nieve->setProbGen(0.2);
    particleSystem->addGenerator(nieve);
}

void ScenePractica::step( double t) //ES EL UPDATE
{
    registry->updateForces(t);
    //PX_UNUSED(interactive);
    if (!proyectil->isEmpty())
    {
        //llamar al integrate de cada bala

        proyectil->shot(t);
    }
    particleSystem->update(t);

    gScene->simulate(t);
    gScene->fetchResults(true);


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
        Vector4 color(1, 0, 0, 1);
        //la pos de la camara como pos inicial de la particula
        proyectil->createBullet(cam->getTransform().p, 300.0, Vector3(0.0f, 250.0f, 0.0f),
            Vector3(0.0f, 0.0f, 0.0f), 0.4f, 15.0f, cam->getDir(), color);
        auto vb = proyectil->getBullets();
        Particle* p = vb[vb.size() - 1];
         registry->addGeneratorToParticle(nullptr,"proyectiles", gravity, p);
 
        break;
    }
    case 'O':
    {
        //bala de tanque

        Camera* cam = GetCamera();
        Vector4 color(0, 1, 0, 1);

        //la pos de la camara como pos inicial de la particula
        proyectil->createBullet(cam->getTransform().p, 100.0, Vector3(0.0f, 1800.0f, 0.0f),
            Vector3(0.0f, -9.8f, 0.0f), 0.4f, 4.0f, cam->getDir(), color);
        auto vb = proyectil->getBullets();
        Particle* p = vb[vb.size() - 1];
        registry->addGeneratorToParticle(nullptr, "proyectiles", gravity, p);
        break;
    }
    case 'I':
    {
        //bala de pistola

        Camera* cam = GetCamera();
        Vector4 color(0, 0, 1, 1);
        proyectil->createBullet(cam->getTransform().p, 1000.0, Vector3(0.0f, 330.0f, 0.0f),
            Vector3(0.0f, -9.8f, 0.0f), 0.4f, 2.6f, cam->getDir(), color);
        auto vb = proyectil->getBullets();
        Particle* p = vb[vb.size() - 1];   
        registry->addGeneratorToParticle(nullptr, "proyectiles", gravity, p);
        break;
    }
    default:
        break;
    }
}

void ScenePractica::cleanup() {
    DeregisterRenderItem(itemX);
    DeregisterRenderItem(itemY);
    DeregisterRenderItem(itemZ);
    delete itemX; delete itemY; delete itemZ;

    if (gScene) gScene->release();
    if (gDispatcher) gDispatcher->release();
    if (gMaterial) gMaterial->release();

    delete proyectil;
   // delete particleSystem;
    delete registry;
    delete gravity;
    delete softGravity;
   // delete wind;
   // delete whirl;
}