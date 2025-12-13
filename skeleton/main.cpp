#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

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
#include "SpringForceGenerator.h"
#include "MuellePracticaSystem.h"
#include "FloatForce.h"
#include "FlotacionPracticaSystem.h"
#include "FontainSystem.h"
#include "CubeSolidSystem.h"
#include "SolidSystem.h"
#include "SphereSolidSystem.h"
#include "muelleMovible.h"

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;
ContactReportCallback gContactReportCallback;


// dianas
RenderItem* itemX = nullptr;
RenderItem* itemY = nullptr;
RenderItem* itemZ = nullptr;

// fuerzas y el registro
Gravity* gravity = nullptr;
Gravity* gravity2 = nullptr;
WindGenerator* wind = nullptr;
OscillateWind* oscillate = nullptr;
Whirlwind* whril = nullptr;

SpringForceGenerator* spring1 = nullptr;
SpringForceGenerator* spring2 = nullptr;
SpringForceGenerator* spring3 = nullptr;

FloatForce* floatP = nullptr;

// particulas  y solidos
ParticleSystem* particleSystem = nullptr;
SolidSystem* solidSystem = nullptr;

// generadores
bool pressedNieve = false;
physx::PxVec3 posGanar;
SparkleSystem* sparSys = nullptr;
SnowSystem* snowSys = nullptr;
BulletSystem* bulletSys = nullptr;
MuellePracticaSystem* muelleSys = nullptr;
FlotacionPracticaSystem* floatSys = nullptr;
//FontainSystem* fuenteSys = nullptr;
CubeSolidSystem* cubeSys = nullptr;
SphereSolidSystem* sphereSys = nullptr;
std::vector<muelleMovible*> muellesMovibles;
muelleMovible* muelleMov = nullptr;
//booleanos para activacion/desactivacion de generadores de fuerzas
bool boolGravity = true;
bool boolWind = true;
bool showSparkle = true;
bool boolOscilate = true;
bool boolSpring1 = true;
bool boolSpring2 = true;
bool boolWhril = true;
int pescados = 4;
bool win = false;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);


	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	/*//Generar suelo
    PxRigidStatic* Suelo = gPhysics->createRigidStatic(PxTransform({ 50,20, -80 }));
    PxShape* shapeSuelo = CreateShape(PxBoxGeometry(100, 0.1, 100));
    Suelo->attachShape(*shapeSuelo);
    gScene->addActor(*Suelo);

    // Pintar suelo
    RenderItem* item;
    item = new RenderItem(shapeSuelo, Suelo, { 0.8, 0.8,0.8,1 });
	*/
	/*// Anadir un actor dinamico
	PxRigidDynamic* new_solid;
	new_solid = gPhysics->createRigidDynamic(PxTransform({ 50,200,-80 }));
	new_solid->setLinearVelocity({ 0,5,0 });
	new_solid->setAngularVelocity({ 0,0,0 });
	PxShape* shape_ad = CreateShape(PxBoxGeometry(5, 5, 5));
	new_solid->attachShape(*shape_ad);

	PxRigidBodyExt::updateMassAndInertia(*new_solid, 0.15);
	gScene->addActor(*new_solid);

	// Pintar actor dinamico
	RenderItem* dynamic_item;
	dynamic_item = new RenderItem(shape_ad, new_solid, { 0.8, 0.8,0.8,1 });

	*/
	// === Dianas ===
	PxSphereGeometry geo(5.0f); //antes para ejes 2
	PxShape* shape = CreateShape(geo, gMaterial);

	//itemX = new RenderItem(shape, new PxTransform(Vector3(50, 40, -80)), Vector4(0, 1, 0, 1));
	//itemY = new RenderItem(shape, new PxTransform(Vector3(00, 0, -80)), Vector4(0, 1, 0, 1));
	//itemZ = new RenderItem(shape, new PxTransform(Vector3(-50, -20, -80)), Vector4(0, 1, 0, 1));


	//ejes antiguos
   /* itemX = new RenderItem(shape, new PxTransform(PxVec3(10, 0, 0)), Vector4(1, 0, 0, 1));
	itemY = new RenderItem(shape, new PxTransform(PxVec3(0, 10, 0)), Vector4(0, 1, 0, 1));
	itemZ = new RenderItem(shape, new PxTransform(PxVec3(0, 0, 10)), Vector4(0, 0, 1, 1));
	//*/
	//RegisterRenderItem(itemX);
	//RegisterRenderItem(itemY);
	//RegisterRenderItem(itemZ);

	// === Fuerzas ===
	gravity = new Gravity(Vector3(0, -90.8f, 0));
	wind = new WindGenerator(Vector3(0.0f, 0.0f, 20000.0f), 0.3f, 0.0f);
	oscillate = new OscillateWind(Vector3(0.0f, 100.0f, 0.0f), 0.5f, 0.1f, 300.0f, 3.0f);
	//spring1 = new SpringForceGenerator(10, 2);
	//spring2 = new SpringForceGenerator(10, 2);
	//spring3 = new SpringForceGenerator(1, 10);
	floatP = new FloatForce(1, 1, 1000);
	//whril = new Whirlwind(200.0f, Vector3(25, 0, 0), Vector3(10.0f, 0.0f, 0.0f), 0.5f, 1.2f);
	gravity2 = new Gravity(Vector3(0, -9.8f, 0));

	// ===  partículas y solidos (sistemas) ===
	particleSystem = new ParticleSystem();
	solidSystem = new SolidSystem();

	//sistemas de particulas 
	bulletSys = new BulletSystem(nullptr, nullptr, nullptr);
	sparSys = new SparkleSystem(gravity, nullptr, oscillate);
	sparSys->ActivateParticle(showSparkle);
	snowSys = new SnowSystem(gravity, nullptr, nullptr);
	//fuenteSys = new FontainSystem(gravity2, whril);
	
	//muelles y flotacion 
	//muelleSys = new MuellePracticaSystem(gravity2, spring1, spring2, spring3);
	//floatSys = new FlotacionPracticaSystem(gravity2, floatP);
	oscillate = new OscillateWind(Vector3(-500, -500, -500), 2.0f, 1.0f, 1.0f, 100.0f);
	Vector3 pos(40, 10, 0); // posición inicial

	for (int i = 0; i < 4; i++)
	{
		muelleMov = new muelleMovible(gravity2,pos); 
		muellesMovibles.push_back(muelleMov);

		pos.y += 20; 
		pos.x -= 10;
	}
	//sistemas de solidos
	
}

void Win()
{
	win = true;
	PxVec3 posCamara(420, 40, -200);
	Camera* cam = GetCamera();
	cam->setTransform(posCamara);

	PxRigidStatic* Suelo = gPhysics->createRigidStatic(PxTransform({ 400, 20, -300 }));
	PxShape* shapeSuelo = CreateShape(PxBoxGeometry(100, 0.1, 100));
	Suelo->attachShape(*shapeSuelo);
	gScene->addActor(*Suelo);

	// Pintar suelo
	RenderItem* item;
	item = new RenderItem(shapeSuelo, Suelo, { 0.8, 0.8,0.8,1 });

	PxVec3 posSolidos(400, 80, -300);

	//sistema solidos 
	cubeSys = new CubeSolidSystem(gPhysics, gScene,gravity2, oscillate, posSolidos);
	cubeSys->ActivateSolid(true);

	sphereSys = new SphereSolidSystem(gPhysics, gScene, gravity2, oscillate);
	sphereSys->ActivateSolid(true);





}

void checkCollision()
{

	for (Particle* b : bulletSys->getBullets())

	{
		for (muelleMovible* m : muellesMovibles)
		{
			float dist = (b->getPos() - m->getPos()).magnitude();

			if (dist < b->getRadius() + m->getRadius())
			{
				if (m->isActive())
				{
					m->deactivate();
					pescados--;
					if (pescados == 0)
					{
						//hemos ganado
						Win();
					}
				}
				b->setAlive(false);
				break;
			}
		}
	}
}
void removeDeadMuelles()
{
	muellesMovibles.erase(
		std::remove_if(muellesMovibles.begin(), muellesMovibles.end(),
			[](muelleMovible* m)
			{
				if (!m->isActive())
				{
					delete m;
					return true;
				}
				return false;
			}),
		muellesMovibles.end()
	);
}
// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

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

		checkCollision();
		removeDeadMuelles();
	
	}
	sparSys->update(t);
	snowSys->update(t);
	// muelleSys->update(t);
	// floatSys->update(t);
	
	if (win)
	{
		cubeSys->update(t);
		sphereSys->update(t);
	}
	
	for (auto elem : muellesMovibles)
	{
		if(elem->isActive())
		elem->update(t);
	}
	gScene->simulate(t);
	gScene->fetchResults(true);

	Camera* cam = GetCamera();

	//aparece "nieve" delimitadora de espacio de disparo
	if (cam->getTransform().p.magnitude() > 140.0)
	{
		snowSys->ActivateParticle(true);
	}
	else
	{
		snowSys->ActivateParticle(false);
	}
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

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
		Vector4 color(0.5, 0, 0, 1);
		//la pos de la camara como pos inicial de la particula

		bulletSys->createBullet(cam->getTransform().p, 200.0, Vector3(0.0f, 1000.0f, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f), 0.4f, 4.0f, cam->getDir(), color);

		break;
	}
	/*case 'O':
	{
		//bala de tanque
		Camera* cam = GetCamera();
			Vector4 color(0, 1, 0, 1);

			bulletSys->createBullet(cam->getTransform().p, 150.0, Vector3(0.0f, 1800.0f, 0.0f),
				Vector3(0.0f, -9.8f, 0.0f), 0.4f, 4.0f, cam->getDir(), color);
		break;
	}*/
	case 'I':
	{
		//bala de pistola

		Camera* cam = GetCamera();
		Vector4 color(0.0, 0.4, 0.07, 1);
		bulletSys->createBullet(cam->getTransform().p, 400.0, Vector3(0.0f, 330.0f, 0.0f),
			Vector3(0.0f, 0.0f, 0.0f), 0.4f, 2.6f, cam->getDir(), color);

		break;
	}
	case 'M':
	{
		//Camera* cam = GetCamera();
	//	cam->setTransform(posGanar);
		Win();
		showSparkle = !showSparkle;
		sparSys->ActivateParticle(showSparkle);


		break;
	}

	case 'Y':
	{
		boolGravity = !boolGravity;
		sparSys->ActivateGravity(boolGravity);
		snowSys->ActivateGravity(boolGravity);
		muelleSys->ActivateGravity(boolGravity);
		floatSys->ActivateGravity(boolGravity);
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
	case 'B':
	{
		boolSpring1 = !boolSpring1;
		boolSpring2 = !boolSpring2;
		muelleSys->ActivateSpring(boolSpring1);
		muelleSys->ActivateSpring(boolSpring2);
		break;
	}
	case 'K':
	{

		muelleSys->setK(10);
		break;
	}
	case 'L':
	{

		muelleSys->setK(-10);
		break;
	}
	case 'C':
	{

		floatSys->AddMasa(100.0f);
		break;
	}
	case 'V':
	{

		floatSys->AddVolume(1.0f);
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char* const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for (PxU32 i = 0; i < frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}