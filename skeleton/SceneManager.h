#pragma once
#include "BaseScene.h"
#include <iostream>

class SceneManager {
private:
    PxPhysics* gPhysics = nullptr;
    BaseScene* currentScene = nullptr;

public:
    SceneManager(PxPhysics* physics);
    ~SceneManager();

    void changeScene(int sceneId);
    void step(double t);
    void onKeyPress(unsigned char key, const PxTransform& camera);
    void cleanup();
};