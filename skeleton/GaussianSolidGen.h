#pragma once
#include "SolidGenerator.h"
#include <vector>
#include <random>
#include "PxPhysicsAPI.h"


enum class SolidShapeType
{
    BOX,
    SPHERE
};

class GaussianSolidGen : public SolidGenerator {
private:
    std::normal_distribution<float> _d;
    std::uniform_real_distribution<float> _u;
    std::mt19937 _mt;
    int n_bodies;
    float probGen;

    physx::PxVec3 posMedia;
    physx::PxVec3 velMedia;
    physx::PxVec3 desvPos;
    physx::PxVec3 desvVel;

    float massMedia;
    float desvMass;

    float sphereRadius = 5.0f;
    SolidShapeType shapeType;
    float size;

public:
    GaussianSolidGen(physx::PxPhysics* p, physx::PxScene* s, physx::PxMaterial* mat, int n);


    void setDesvPos(physx::PxVec3 d);
    void setDesvVel(physx::PxVec3 d);
    void setPosMedia(physx::PxVec3 p);
    void setVelMedia(physx::PxVec3 v);

    void setProbGen(float a);

    std::vector<physx::PxRigidDynamic*> generateRigidBodies() override;

    void setShapeType(SolidShapeType t);
    float getSize();
    void setSize(float halfExtents);     // Para BOX
    void setRadius(float r);                            // Para SPHERE / CAPSULE
    void setMassMedia(float m);
    void setDesvMass(float d);
};