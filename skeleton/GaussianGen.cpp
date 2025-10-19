#include "GaussianGen.h"

GaussianGen::GaussianGen()
{
	posMedia = { 30.0f, 0.0f, 0.0f };    
	velMedia = { 0.0f, 100.0f, 0.0f };   
	durMedia = 10.0f;                     

	desvP = { 5.0f, 1.0f, 5.0f };        
	desvV = { 15.0f, 30.0f, 15.0f };     
	desvD = 1.0f;

	n_particles = 80;
}

list<Particle*> GaussianGen::generateP()
{
    list<Particle*> newParticles;  // lista local para nuevas partículas

    for (int i = 0; i < n_particles; i++)
    {
        if (_u(_mt) > 0.5)
        {
            pos = posMedia + desvP * _d(_mt);
            vel = velMedia + desvV * _d(_mt);
            dur = durMedia + desvD * _d(_mt);

             modelo = new Particle(dur, pos, vel, Vector3(0.0f, 1800.0f, 0.0f),
                Vector3(0.0f, -9.8f, 0.0f), 0.4f, 0.0f, 0.0f,
                Vector4(0, 1, 0, 1));

            newParticles.push_back(modelo);
        }
    }
    return newParticles;
	
}
