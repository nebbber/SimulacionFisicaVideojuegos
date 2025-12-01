#include "SceneManager.h"
#include "ScenePractica.h"

SceneManager::SceneManager()
    : gPhysics(nullptr) {
}

SceneManager::~SceneManager() {
    cleanup();
}

void SceneManager::changeScene(int sceneId) {
    // Limpiar la escena actual si existe
    if (currentScene) {
        currentScene->cleanup();
        delete currentScene;
        currentScene = nullptr;
    }

    // Crear la nueva escena
    switch (sceneId) {
    case 0:
        currentScene = new ScenePractica();
        break;
    case 1:
       // std::cout << "→ Cargando Escena Proyecto...\n";
       // currentScene = new SceneJuego(gPhysics);
        break;
    default:
       
        return;
    }

    // Inicializar la nueva escena
    currentScene->init();
}

void SceneManager::step(double t) {
    if (currentScene)
        currentScene->step(t);
}

void SceneManager::onKeyPress(unsigned char key, const PxTransform& camera) {
    // Controlar cambio de escenas
    if (key == '1') {
        //changeScene(0);
    }
    else if (key == '2') {
        //changeScene(1);
    }
    else if (currentScene) {
        currentScene->onKeyPress(key, camera);
    }
}

void SceneManager::cleanup() {
    if (currentScene) {
        currentScene->cleanup();
        delete currentScene;
        currentScene = nullptr;
    }
}
void SceneManager::onCollision(PxActor* actor1, PxActor* actor2) {
    if (currentScene)
        currentScene->onCollision(actor1, actor2);
}