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


    Vector3 f;
    f.x = -K * dir.z; 
    f.y = K * (50 - dir.y); 
    f.z = K * dir.x;  

    p->addForce(f);
}