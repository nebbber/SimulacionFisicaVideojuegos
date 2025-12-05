#include "GaussianSolidGen.h"
#include "PxPhysicsAPI.h"

GaussianSolidGen::GaussianSolidGen(physx::PxPhysics* p, physx::PxScene* s, physx::PxMaterial* mat, int n)
    : SolidGenerator(p, s, mat), n_bodies(n), _d(0.f, 1.f), probGen(1.0f), massMedia(1.f), desvMass(0.2f)
{
    std::random_device rd;
    _mt = std::mt19937(rd());

    posMedia = physx::PxVec3(0.f);
    velMedia = physx::PxVec3(0.f);
    desvPos = physx::PxVec3(0.f);
    desvVel = physx::PxVec3(0.f);
}

void GaussianSolidGen::setDesvPos(physx::PxVec3 d)
{
    desvPos = d;
}

void GaussianSolidGen::setDesvVel(physx::PxVec3 d)
{
    desvVel = d;
}

void GaussianSolidGen::setPosMedia(physx::PxVec3 p)
{
    posMedia = p;
}

void GaussianSolidGen::setVelMedia(physx::PxVec3 v)
{
    velMedia = v;
}

std::vector<physx::PxRigidDynamic*> GaussianSolidGen::generateRigidBodies()
{
    std::vector<physx::PxRigidDynamic*> newBodies;

    for (int i = 0; i < n_bodies; i++)
    {
        // Decide si generamos este cuerpo
        if (std::uniform_real_distribution<float>(0.f, 1.f)(_mt) < probGen)
        {
            // Generar posición y velocidad con distribución gaussiana
            physx::PxVec3 pos(
                posMedia.x + desvPos.x * _d(_mt),
                posMedia.y + desvPos.y * _d(_mt),
                posMedia.z + desvPos.z * _d(_mt)
            );

            physx::PxVec3 vel(
                velMedia.x + desvVel.x * _d(_mt),
                velMedia.y + desvVel.y * _d(_mt),
                velMedia.z + desvVel.z * _d(_mt)
            );

            float mass = massMedia + desvMass * _d(_mt);

            // Crear cuerpo rígido dinámico
            physx::PxRigidDynamic* body = physics->createRigidDynamic(physx::PxTransform(pos));

            // Crear forma geométrica (cubo)
            physx::PxBoxGeometry geom(0.5f, 0.5f, 0.5f);
            physx::PxShape* shape = physics->createShape(geom, *defaultMat);
            body->attachShape(*shape);

            // Actualizar masa e inercia
            physx::PxRigidBodyExt::updateMassAndInertia(*body, mass);

            // Velocidad inicial
            body->setLinearVelocity(vel);

            // Añadir a la escena
            scene->addActor(*body);

            newBodies.push_back(body);
        }
    }

    return newBodies;
}