#include "GaussianSolidGen.h"
#include "PxPhysicsAPI.h"

GaussianSolidGen::GaussianSolidGen(physx::PxPhysics* p, physx::PxScene* s, physx::PxMaterial* mat, int n)
    : SolidGenerator(p, s, mat), n_bodies(n), _d(0.f, 1.f), probGen(1.0f), massMedia(1.f), desvMass(0.2f), _u(0.0f, 1.0f)
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

void GaussianSolidGen::setProbGen(float a)
{
    probGen = a;
}

std::vector<physx::PxRigidDynamic*> GaussianSolidGen::generateRigidBodies()
{
    std::vector<physx::PxRigidDynamic*> newBodies;

    for (int i = 0; i < n_bodies; i++)
    {
       
        if (_u(_mt) < probGen)
        {
            // Posición inicial
            physx::PxVec3 pos(
                posMedia.x + desvPos.x * _d(_mt),
                posMedia.y + desvPos.y * _d(_mt),
                posMedia.z + desvPos.z * _d(_mt)
            );

            // Evitar que el cubo se genere dentro del suelo
           // float halfExtent = 5.0f; // Igual que tu cubo manual
            if (pos.y < size) pos.y = size;

            // Velocidad inicial
            physx::PxVec3 vel(
                velMedia.x + desvVel.x * _d(_mt),
                velMedia.y + desvVel.y * _d(_mt) + 2.0f, // Pequeño impulso hacia arriba
                velMedia.z + desvVel.z * _d(_mt)
            );

            // Masa
            float mass = massMedia + desvMass * _d(_mt);
            if (mass < 0.1f) mass = 0.1f; // Evitar masa demasiado pequeña

            // Crear cuerpo dinámico
            physx::PxRigidDynamic* body = physics->createRigidDynamic(physx::PxTransform(pos));

            // Geometría del cubo
           /* physx::PxBoxGeometry geom(size, size, size);
            physx::PxShape* shape = physics->createShape(geom, *defaultMat);*/
            // Geometría del cubo
            

            // Crear forma según tipo
            physx::PxShape* shape = nullptr;
            switch (shapeType)
            {
            case SolidShapeType::BOX:
            {
                physx::PxBoxGeometry geom(size, size, size);
                shape = physics->createShape(geom, *defaultMat);
                break;
            }
            case SolidShapeType::SPHERE:
            {
                physx::PxSphereGeometry geom(sphereRadius);
                shape = physics->createShape(geom, *defaultMat);
                break;
            }
            }
            body->attachShape(*shape);

            // Actualizar masa e inercia
            physx::PxRigidBodyExt::updateMassAndInertia(*body, mass);

            // Velocidad inicial
            body->setLinearVelocity(vel);
            body->setAngularVelocity(physx::PxVec3(0, 0, 0));


            // Añadir a la escena
            scene->addActor(*body);

            newBodies.push_back(body);
        }
    }

    return newBodies;
}
void GaussianSolidGen::setShapeType(SolidShapeType t)
{
    shapeType = t;
}
float GaussianSolidGen::getSize()
{
    return size;
}
void GaussianSolidGen::setSize(float halfExtents)
{
    size = halfExtents;
}

void GaussianSolidGen::setMassMedia(float m)
{
    massMedia = m;
}

void GaussianSolidGen::setDesvMass(float d)
{
    desvMass = d;
}
