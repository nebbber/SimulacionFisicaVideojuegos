#include "GaussianSolidGen.h"

GaussianRigidGen::GaussianRigidGen(PxPhysics* p, PxScene* s, PxMaterial* mat, int n)
    : SolidGenerator(p, s, mat), n_bodies(n), _d(0.f, 1.f), probGen(1.0f), massMedia(1.f), desvMass(0.2f)
{
    std::random_device rd;
    _mt = std::mt19937(rd());
    posMedia = PxVec3(0.f);
    velMedia = PxVec3(0.f);
    desvPos = PxVec3(0.f);
    desvVel = PxVec3(0.f);
}

void GaussianRigidGen::setDesvPos(PxVec3 d)
{
    desvPos = d;
}

void GaussianRigidGen::setDesvVel(PxVec3 d)
{
    desvVel = d;
}

void GaussianRigidGen::setPosMedia(PxVec3 p)
{
    posMedia = p;
}

void GaussianRigidGen::setVelMedia(PxVec3 v)
{
    velMedia = v;
}

std::vector<PxRigidDynamic*> GaussianRigidGen::generateRigidBodies()
{
    std::vector<PxRigidDynamic*> newBodies;

    for (int i = 0; i < n_bodies; i++)
    {
        if (std::uniform_real_distribution<float>(0.f, 1.f)(_mt) < probGen)
        {
            // Generar posición y velocidad
            PxVec3 pos(
                posMedia.x + desvPos.x * _d(_mt),
                posMedia.y + desvPos.y * _d(_mt),
                posMedia.z + desvPos.z * _d(_mt)
            );

            PxVec3 vel(
                velMedia.x + desvVel.x * _d(_mt),
                velMedia.y + desvVel.y * _d(_mt),
                velMedia.z + desvVel.z * _d(_mt)
            );

            float mass = massMedia + desvMass * _d(_mt);

           
            PxRigidDynamic* body = physics->createRigidDynamic(PxTransform(pos));

            // geo
            PxBoxGeometry geom(0.5f, 0.5f, 0.5f);
            PxShape* shape = physics->createShape(geom, *defaultMat);
            body->attachShape(*shape);

            PxRigidBodyExt::updateMassAndInertia(*body, mass);

            // vel inicial
            body->setLinearVelocity(vel);

            // add a la escena
            scene->addActor(*body);
            newBodies.push_back(body);
        }
    }

    return newBodies;
}