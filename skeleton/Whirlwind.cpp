#include "Whirlwind.h"
#include <iostream>
Whirlwind::Whirlwind(float _K, Vector3 _posCentro, Vector3 vel, float k1, float k2):WindGenerator(vel,k1,k2)
{
    posCentro = _posCentro;
    K = _K;
    velViento = vel;
}

Whirlwind::~Whirlwind()
{

}
void Whirlwind::update(double t, Particle* p)
{
    Vector3 posPart = p->getPos();
    Vector3 dir = posPart - posCentro;

    // Distancia al cuadrado
    float dist2 = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
    if (dist2 < 0.0001f) return; // Evitar división por cero

    // Vector tangencial alrededor del eje Y (torbellino clásico)
    Vector3 tang;
    tang.x = -dir.z;
    tang.y = 0;
    tang.z = dir.x;

    // No normalizo, solo escalo por 1/distancia
    float invDist = 1.0f / sqrt(dist2); // si NO tienes sqrt, dime y te doy otra versión

    // Fuerza tangencial (rotación)
    Vector3 f;
    f.x = K * tang.x * invDist;
    f.y = K * (posCentro.y - posPart.y) * 0.3f; // succión vertical suave
    f.z = K * tang.z * invDist;

    p->addForce(f);
}
void Whirlwind::update(double t, PxRigidDynamic* r)
{
    PxVec3 posPart = r->getGlobalPose().p;
    PxVec3 dir = posPart - PxVec3(posCentro.x, posCentro.y, posCentro.z);

    float dist2 = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
    if (dist2 < 0.0001f) return;

    PxVec3 tang(-dir.z, 0, dir.x);
    float invDist = 1.0f / std::sqrt(dist2);

    PxVec3 force;
    force.x = K * tang.x * invDist;
    force.y = K * (posCentro.y - posPart.y) * 0.3f;
    force.z = K * tang.z * invDist;

    r->addForce(force);
}