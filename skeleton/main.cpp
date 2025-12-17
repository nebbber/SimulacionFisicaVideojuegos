#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "BackgroundWaterSystem.h"
#include "BulletSystem.h"
#include "ParticleSystem.h"
#include "ForceRegistry.h"
#include "Gravity.h"
#include "WindGenerator.h"
#include "Whirlwind.h"
#include "UniformGen.h"
#include "GaussianGen.h"
#include "OscillateWind.h"
#include "OutOfRangeSystem.h"
#include "SpringForceGenerator.h"
#include "MuellePracticaSystem.h"
#include "FloatForce.h"
#include "FlotacionPracticaSystem.h"
#include "BreathWater.h"
#include "CubeSolidSystem.h"
#include "SolidSystem.h"
#include "SphereSolidSystem.h"
#include "muelleMovible.h"
#include "FontainSystem.h"

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


// fuerzas y el registro
Gravity* gravity = nullptr;
Gravity* gravity2 = nullptr;
WindGenerator* wind = nullptr;
OscillateWind* oscillate = nullptr;
Whirlwind* whril = nullptr;
SpringForceGenerator* spring1 = nullptr;
SpringForceGenerator* spring2 = nullptr;
FloatForce* floatP = nullptr;
OscillateWind* oscillate2 = nullptr;
// particulas  y solidos
ParticleSystem* particleSystem = nullptr;
SolidSystem* solidSystem = nullptr;

// sistemas particulas y solidos
BackgroundWaterSystem* backWaterSys = nullptr;
OutOfRangeSystem* outRangeSys = nullptr;
BulletSystem* bulletSys = nullptr;
MuellePracticaSystem* muelleSys = nullptr;
FlotacionPracticaSystem* floatSys = nullptr;
FontainSystem* fontainSys = nullptr;
std::vector<muelleMovible*> muellesMovibles;
muelleMovible* muelleMov = nullptr;

CubeSolidSystem* cubeSys = nullptr;
SphereSolidSystem* sphereSys = nullptr;


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

	
	//PxSphereGeometry geo(5.0f); //antes para ejes 2
	//PxShape* shape = CreateShape(geo, gMaterial);

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
	spring1 = new SpringForceGenerator(10, 2);
	spring2 = new SpringForceGenerator(10, 2);
	floatP = new FloatForce(1, 1, 1000);
	whril = new Whirlwind(10.0f,Vector3(600, 0, 0),Vector3(0, 0, 0),0.2f,2.0f);
	gravity2 = new Gravity(Vector3(0, -9.8f, 0));
	oscillate2 = new OscillateWind(Vector3(-500, -500, -500), 2.0f, 1.0f, 1.0f, 100.0f);

	// ===  partículas y solidos (sistemas) ===
	particleSystem = new ParticleSystem();
	solidSystem = new SolidSystem();

	//sistemas de particulas 
	bulletSys = new BulletSystem(nullptr, nullptr, nullptr);
	backWaterSys = new BackgroundWaterSystem(gravity, nullptr, oscillate);
	backWaterSys->ActivateParticle(showSparkle);
	outRangeSys = new OutOfRangeSystem(gravity, nullptr, nullptr);
	

	Vector3 pos(40, 10, 0); // posición inicial muelles movibles (los peces)

	for (int i = 0; i < 4; i++)
	{
		muelleMov = new muelleMovible(gravity2,pos); 
		muellesMovibles.push_back(muelleMov);

		pos.y += 20; 
		pos.x -= 10;
	}
	
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
	item = new RenderItem(shapeSuelo, Suelo, Vector4( 0.6f, 0.4f, 0.2f, 1.0f ));

	//crear jugador/capsula
	PxTransform poseCapsula(
		PxVec3(400, 30, -300),                 
		PxQuat(PxPi / 2, PxVec3(0, 0, 1))     
	);

	PxRigidStatic* capsula = gPhysics->createRigidStatic(poseCapsula);

	PxShape* shapeCapsula = CreateShape(
		PxCapsuleGeometry(2.0f, 4.0f),
		gMaterial
	);

	capsula->attachShape(*shapeCapsula);
	gScene->addActor(*capsula);


	RenderItem* itemCapsula =
		new RenderItem(shapeCapsula, capsula, Vector4(0, 0, 1, 1));


	//crear sistema solidos
	PxVec3 posCajas(400, 60, -250);
	PxVec3 posConfetti(440, 100, -300);
	//sistema solidos 
	cubeSys = new CubeSolidSystem(gPhysics, gScene,gravity2, oscillate2, posCajas);
	cubeSys->ActivateSolid(true);

	sphereSys = new SphereSolidSystem(gPhysics, gScene, gravity2, oscillate2, posConfetti);
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

	//PX_UNUSED(interactive);
	if (!bulletSys->isEmpty())
	{
		//llamar al integrate de cada bala

		bulletSys->shot(t);

		checkCollision();
		removeDeadMuelles();
	
	}
	backWaterSys->update(t);
	outRangeSys->update(t);


	if (muelleSys != nullptr && floatSys != nullptr&&fontainSys!= nullptr)
	{
		muelleSys->update(t);
		floatSys->update(t);
		fontainSys->update(t);
	}
	
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

	//aparecen particulas delimitadora de espacio de disparo
	if (cam->getTransform().p.magnitude() > 140.0)
	{
		outRangeSys->ActivateParticle(true);
	}
	else
	{
		outRangeSys->ActivateParticle(false);
	}
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	

	// ===================== Fuerzas =====================
	delete gravity; gravity = nullptr;
	delete gravity2; gravity2 = nullptr;
	delete wind; wind = nullptr;
	delete oscillate; oscillate = nullptr;
	delete oscillate2; oscillate2 = nullptr;
	delete whril; whril = nullptr;
	delete spring1; spring1 = nullptr;
	delete spring2; spring2 = nullptr;
	delete floatP; floatP = nullptr;

	// ===================== Sistemas de partículas =====================
	// Estos destructores ya borran sus partículas internas y el registry
	delete particleSystem; particleSystem = nullptr;
	delete solidSystem; solidSystem = nullptr;
	delete backWaterSys; backWaterSys = nullptr;
	delete outRangeSys; outRangeSys = nullptr;
	delete bulletSys; bulletSys = nullptr;
	delete muelleSys; muelleSys = nullptr;
	delete floatSys; floatSys = nullptr;
	delete fontainSys; fontainSys = nullptr;

	// ===================== Muelles movibles =====================
	for (auto m : muellesMovibles) delete m;
	muellesMovibles.clear();
	muelleMov = nullptr;

	// ===================== Sistemas de sólidos =====================
	delete cubeSys; cubeSys = nullptr;
	delete sphereSys; sphereSys = nullptr;

	// ===================== PhysX =====================
	if (gScene) gScene->release();
	if (gDispatcher) gDispatcher->release();
	if (gPhysics) gPhysics->release();

	if (gPvd)
	{
		PxPvdTransport* transport = gPvd->getTransport();
		gPvd->release();
		if (transport) transport->release();
	}

	if (gFoundation) gFoundation->release();


	gScene = nullptr;
	gDispatcher = nullptr;
	gPhysics = nullptr;
	gPvd = nullptr;
	gFoundation = nullptr;
	gMaterial = nullptr;
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
	case 'Z':
	{
		PxVec3 posCamara(700, 40, 100);
		Camera* cam = GetCamera();
		cam->setTransform(posCamara);
		if (muelleSys==nullptr&&floatSys==nullptr&& fontainSys==nullptr)
		{
			muelleSys = new MuellePracticaSystem(gravity2, spring1,spring2);
			floatSys = new FlotacionPracticaSystem(gravity2, floatP);
			fontainSys = new FontainSystem(nullptr,whril);
			

		}
		
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
		
		showSparkle = !showSparkle;
		backWaterSys->ActivateParticle(showSparkle);

		break;
	}
	case 'F':
	{
		boolWhril = !boolWhril;
		if (fontainSys)
		{
			fontainSys->ActivateWhril(boolWhril);
		}

		break;
	}
	case 'O':
	{
		Win();
		break;
	}

	case 'Y':
	{
		boolGravity = !boolGravity;
		backWaterSys->ActivateGravity(boolGravity);
		outRangeSys->ActivateGravity(boolGravity);

		if (muelleSys && floatSys&& fontainSys)
		{
			muelleSys->ActivateGravity(boolGravity);
			floatSys->ActivateGravity(boolGravity);
			fontainSys->ActivateGravity(boolGravity);
		}

		break;
	}
	case 'T':
	{
		boolWind = !boolWind;
		outRangeSys->ActivateWind(boolWind);

		
		break;
	}
	case 'R':
	{
		boolOscilate = !boolOscilate;
		backWaterSys->ActivateOscilate(boolOscilate);
		if ( sphereSys != nullptr)
		{
			sphereSys->ActivateOscilate(boolOscilate);
		}
		break;
	}
	case 'B':
	{
		if (muelleSys)
		{
			boolSpring1 = !boolSpring1;
			boolSpring2 = !boolSpring2;
			muelleSys->ActivateSpring(boolSpring1);
			muelleSys->ActivateSpring(boolSpring2);
		}
		break;
	}
	case 'K':
	{
		if (muelleSys)
		{
			muelleSys->setK(10);
		}
	
		break;
	}
	case 'L':
	{
		if (muelleSys)
		{
			muelleSys->setK(-10);
		}
		
		break;
	}
	case 'C':
	{
		if (floatSys)
		{
			floatSys->AddMasa(100.0f);
		}
		
		break;
	}
	case 'V':
	{
		if (floatSys)
		{
			floatSys->AddVolume(1.0f);
		}
		
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