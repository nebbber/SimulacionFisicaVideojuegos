#include "UniformGen.h"
#include <algorithm> // para std::max
UniformGen::UniformGen():_r(-1.0, 1.0)
{
    

    desvP = { 0.0f,0.0f,0.0f };
    desvV = { 0.0f,0.0f,0.0f };
    desvD = 0.5f;

}

UniformGen::~UniformGen()
{
    delete modelo;
}

void UniformGen::setDesP(Vector3 p)
{
    desvP = p;
}

void UniformGen::setDesV(Vector3 v)
{
    desvV = v;
}

list<Particle*> UniformGen::generateP()
{
    list<Particle*> newParticles;  // lista para nuevas partículas

    for (int i = 0; i < n_particles; i++)
    {
        if (_u(_mt) < probGen)
        {
            modelo = pModelo->clone();
            //la pos es la de la particula que luego tengo que hacer un set
            Vector3 pos, vel;
            double dur;
            pos.x = posMedia.x + desvP.x * _r(_mt);
            pos.y = posMedia.y + desvP.y * _r(_mt);
            pos.z = posMedia.z + desvP.z * _r(_mt);

            vel.x = velMedia.x + desvV.x * _r(_mt);
            vel.y = velMedia.y + desvV.y * _r(_mt);
            vel.z = velMedia.z + desvV.z * _r(_mt);

            dur = durMedia + desvD * _r(_mt);

            modelo->setPos(pos);
            modelo->setDur(dur);
            modelo->setVel(vel);

            newParticles.push_back(modelo);
        }
    }
    return newParticles;

}
