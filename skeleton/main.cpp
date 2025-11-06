#include <PxPhysicsAPI.h>
#include <iostream>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "SceneManager.h"
#include "ScenePractica.h"
std::string display_text = "This is a test";
using namespace physx;

// ============================================================
// Variables globales PhysX
// ============================================================
PxDefaultAllocator      gAllocator;
PxDefaultErrorCallback  gErrorCallback;
PxFoundation* gFoundation = nullptr;
PxPhysics* gPhysics = nullptr;
PxPvd* gPvd = nullptr;
PxMaterial* gMaterial = nullptr;

// ============================================================
// SceneManager global
// ============================================================
SceneManager* gSceneManager = nullptr;

// ============================================================
// Funciones auxiliares
// ============================================================
void SetSceneManager(SceneManager* manager) { gSceneManager = manager; }

void Step(double t) {
	if (gSceneManager)
		gSceneManager->step(t);
}

void KeyPress(unsigned char key, const PxTransform& camera) {
	if (gSceneManager)
		gSceneManager->onKeyPress(key, camera);
}

void Cleanup() {
	if (gSceneManager)
		gSceneManager->cleanup();
}

// ============================================================
// Inicialización de PhysX base
// ============================================================
void initPhysXBase() {
	std::cout << "[INFO] Inicializando PhysX base..." << std::endl;

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);
	if (!gFoundation) {
		std::cerr << "[ERROR] No se pudo crear PxFoundation" << std::endl;
		return;
	}

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);
	if (!gPhysics) {
		std::cerr << "[ERROR] No se pudo crear PxPhysics" << std::endl;
		return;
	}

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	if (!gMaterial) {
		std::cerr << "[ERROR] No se pudo crear material global" << std::endl;
	}
}

// ============================================================
// Callbacks requeridos por el motor (core.cpp / renderLoop)
// ============================================================
void initPhysics(bool interactive) {
	PX_UNUSED(interactive);
	// Ya está inicializado desde main()
}

void stepPhysics(bool interactive, double t) {
	PX_UNUSED(interactive);
	Step(t);
}

void cleanupPhysics(bool interactive) {
	PX_UNUSED(interactive);
	Cleanup();
}

void keyPress(unsigned char key, const PxTransform& camera) {
	KeyPress(key, camera);
}

// ============================================================
// MAIN PRINCIPAL
// ============================================================
int main(int, const char* const*) {
#ifndef OFFLINE_EXECUTION
	extern void renderLoop(); // implementado en el motor de render (core.cpp)

	// --- Inicializar PhysX base ---
	initPhysXBase();

	if (!gPhysics) {
		std::cerr << "[ERROR] PhysX no se inicializó correctamente" << std::endl;
		return -1;
	}

	// --- Crear SceneManager ---
	SceneManager sceneManager(gPhysics);
	SetSceneManager(&sceneManager);

	// --- Cargar primera escena (ScenePractica) ---
	sceneManager.changeScene(0);

	// --- Iniciar render ---
	renderLoop();

	// --- Limpiar ---
	sceneManager.cleanup();

#else
	// --- Ejecución offline ---
	initPhysXBase();

	SceneManager sceneManager(gPhysics);
	SetSceneManager(&sceneManager);
	sceneManager.changeScene(0);

	const PxU32 frameCount = 100;
	for (PxU32 i = 0; i < frameCount; ++i)
		sceneManager.step(0.016); // 60 FPS

	sceneManager.cleanup();
#endif

	// --- Liberar PhysX ---
	if (gPhysics) gPhysics->release();
	if (gPvd) {
		PxPvdTransport* transport = gPvd->getTransport();
		gPvd->release();
		transport->release();
	}
	if (gFoundation) gFoundation->release();

	std::cout << "[INFO] Finalización completa." << std::endl;
	return 0;
}