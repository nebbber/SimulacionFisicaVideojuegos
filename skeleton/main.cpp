#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Vector3D.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "Proyectil.h"
#include <iostream>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
RenderItem* item1;
RenderItem* item2;
RenderItem* item3;
RenderItem* item;
Particle* particle;
Proyectil* proyectil;
ParticleSystem* particlesys;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);


	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	//creamos ejes
	PxSphereGeometry geo1 = PxSphereGeometry(); //creamos geometria
	geo1.radius = 2;
	PxShape* sphere1 = CreateShape(geo1, gMaterial);//creamos forma

	Vector3D v1(10, 0, 0);
	Vector3D v2(0,10, 0);
	Vector3D v3(0, 0, 10);


	PxTransform* tr1 = new PxTransform(PxVec3(v1.getX(), v1.getY(), v1.getZ()));
	PxTransform* tr2 = new PxTransform(PxVec3(v2.getX(), v2.getY(), v2.getZ()));
	PxTransform* tr3 = new PxTransform(PxVec3(v3.getX(), v3.getY(), v3.getZ()));

	item1 = new RenderItem(sphere1,tr1 , Vector4(1, 0, 0, 1));//renderizamos item
	item2 = new RenderItem(sphere1, tr2, Vector4(0, 1, 0, 1));//renderizamos item
	item3 = new RenderItem(sphere1, tr3, Vector4(0, 0, 1, 1));//renderizamos item
	RegisterRenderItem(item1);//registramos el item a renderizar
	RegisterRenderItem(item2);//registramos el item a renderizar
	RegisterRenderItem(item3);//registramos el item a renderizar
	proyectil = new Proyectil();
	particlesys = new ParticleSystem();


	
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t) //ES EL UPDATE
{
	PX_UNUSED(interactive);
	if (!proyectil->isEmpty())
	{
		//llamar al integrate de cada bala
		proyectil->shot(t);
	}
	particlesys->update(t);
	
	gScene->simulate(t);
	gScene->fetchResults(true);
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

	//DeregisterRenderItem(item);
	DeregisterRenderItem(item1);
	DeregisterRenderItem(item2);
	DeregisterRenderItem(item3);

	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
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
		Vector4 color(1,0,0,1);
		//la pos de la camara como pos inicial de la particula
		proyectil->createBullet(cam->getTransform().p, 300.0, Vector3(0.0f, 250.0f, 0.0f),
			Vector3(0.0f, -9.8f, 0.0f), 0.4f, 15.0f, cam->getDir(),color);
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
		break;
	}
	case 'I':
	{
		//bala de pistola
	
		Camera* cam = GetCamera();
		Vector4 color(0, 0, 1, 1);
		proyectil->createBullet(cam->getTransform().p, 1000.0, Vector3(0.0f, 330.0f, 0.0f),
			Vector3(0.0f, -9.8f, 0.0f), 0.4f, 2.6f, cam->getDir(), color);
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


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}