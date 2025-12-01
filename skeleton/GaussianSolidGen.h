#pragma once
#include "SolidGenerator.h"
#include <random>
#include <vector>
using namespace std;

class GaussianRigidGen : public SolidGenerator {
private:
    std::normal_distribution<float> _d;
    std::mt19937 _mt;
    int n_bodies;
    float probGen;

    PxVec3 posMedia;
    PxVec3 velMedia;
    PxVec3 desvPos;
    PxVec3 desvVel;

    float massMedia;
    float desvMass;

public:
    GaussianRigidGen(PxPhysics* p, PxScene* s, PxMaterial* mat, int n);
    void setDesvPos(PxVec3 d);
    void setDesvVel(PxVec3 d);
    void setPosMedia(PxVec3 p);
    void setVelMedia(PxVec3 v);

    std::vector<PxRigidDynamic*> generateRigidBodies() override;
};