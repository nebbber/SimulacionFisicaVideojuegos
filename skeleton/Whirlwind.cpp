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
    Vector3 pos = p->getPos();
    Vector3 dir = pos - posCentro;

    // Solo XZ
    dir.y = 0.0f;

    float dist2 = dir.x * dir.x + dir.z * dir.z;
    if (dist2 < 1.0f) return;

    float dist = sqrt(dist2);

    // Radio máximo
    float maxRadius = 300.0f;
    if (dist > maxRadius) return;

    // Tangente (perpendicular perfecta)
    Vector3 tang(-dir.z, 0.0f, dir.x);
    tang.normalize();

    // --- FUERZA TANGENCIAL FUERTE ---
    float tangentialForce = K * 50.0f;

    // --- SUCCIÓN RADIAL ---
    Vector3 radial = -dir;
    radial.normalize();
    float suctionForce = K * 30.0f;

    // --- FUERZA FINAL ---
    Vector3 f;
    f = tang * tangentialForce;
    f += radial * suctionForce;

    // --- ELEVACIÓN ---
    f.y = K * 20.0f;

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