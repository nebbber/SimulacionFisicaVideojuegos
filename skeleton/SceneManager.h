#pragma once
#include "BaseScene.h"
#include <iostream>

class SceneManager {
private:
    PxPhysics* gPhysics = nullptr;
    BaseScene* currentScene = nullptr;

public:
    SceneManager();
    ~SceneManager();

    void changeScene(int sceneId);
    void step(double t);
    void onKeyPress(unsigned char key, const PxTransform& camera);
    void cleanup();
    void onCollision(physx::PxActor* actor1, physx::PxActor* actor2);
};