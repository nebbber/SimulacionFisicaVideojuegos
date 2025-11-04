#include "GaussianGen.h"
#include <algorithm> // para std::max
GaussianGen::GaussianGen(std::string nam) : ParticleGen(nam), _d(0.0, 1.0) // media 0, desviación 1
{
    desvP = { 0.0f,0.0f,0.0f }; 
    desvV = { 0.0f,0.0f,0.0f };
    desvD = 0.5f;

}

GaussianGen::~GaussianGen()
{
    delete modelo;
}

void GaussianGen::setDesP( Vector3 p)
{
    desvP = p;
}

void GaussianGen::setDesV(Vector3 v)
{
    desvV = v;
}

list<Particle*> GaussianGen::generateP()
{
    list<Particle*> newParticles;  // lista para nuevas partículas
    if (!isActive) return newParticles;
    for (int i = 0; i < n_particles; i++)
    {
        if (_u(_mt) <probGen)
        {

            modelo = pModelo->clone();
            //la pos es la de la particula que luego tengo que hacer un set
            Vector3 pos,vel;
            double dur;
            pos.x = posMedia.x + desvP.x * _d(_mt);
            pos.y = posMedia.y + desvP.y * _d(_mt);
            pos.z = posMedia.z + desvP.z * _d(_mt);

            vel.x = velMedia.x + desvV.x * _d(_mt);
            vel.y = velMedia.y + desvV.y * _d(_mt);
            vel.z = velMedia.z + desvV.z * _d(_mt);

            dur = durMedia + desvD * _d(_mt);

            modelo->setPos(pos);
            modelo->setDur(dur);
            modelo->setVel(vel);
           
            newParticles.push_back(modelo);
        }
    }
    return newParticles;
	
}
