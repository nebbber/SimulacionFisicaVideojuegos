#include "MuellePracticaSystem.h"
#include "OscillateWind.h"
#include "Gravity.h"
#include "ForceRegistry.h"
#include "SpringForceGenerator.h"
#include "GaussianGen.h"
//poner la gravedad de parametro y asi la tiene
MuellePracticaSystem::MuellePracticaSystem(Gravity* g,SpringForceGenerator* s1, SpringForceGenerator* s2, SpringForceGenerator* s3) :ParticleSystem()
{
    _gravity = g;
    _spring1 = s1;
   _spring2 = s2;
    _spring3 = s3;
   
    _registry = new ForceRegistry();
  
    ptoAnclajeCubo = new Particle(700.0, Vector3(700, 40, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.4f, 20.0f, Vector4(1.0f, 0.0f, 0.5f, 1.0f), 1.0f);
    ptoAnclajeCubo->setShape(2);//que sea cubo
    ptoAnclajeCubo->setGeometry();
  

    p1Muelles = new Particle(700.0, Vector3(700, 10, 0), Vector3(20.0f, 0, 0), Vector3(0, 0, 0), 0.4f, 1.0f, Vector4(1.0f, 0.0f, 0.5f, 1.0f), 1.0f);
    p1Muelles->setGeometry();
    p2Muelles = new Particle(700.0, Vector3(700, 37, 0), Vector3(20.0f, 0, 0), Vector3(0, 0, 0), 0.4f, 1.0f, Vector4(1.0f, 0.0f, 0.5f, 1.0f), 1.0f);
    p2Muelles->setGeometry();


    _particles.push_back(ptoAnclajeCubo);
    _particles.push_back(p1Muelles);
    _particles.push_back(p2Muelles);




    _spring1->setParticle(ptoAnclajeCubo);
    _registry->add(p1Muelles, _spring1); //la que voy a mover

    _spring2->setParticle(p1Muelles);//la de anclaje
    _registry->add(p2Muelles, _spring2);


    _registry->add(p1Muelles, _gravity);
    _registry->add(p2Muelles, _gravity);
    active = true;
}

void MuellePracticaSystem::update(double t)
{
    if (!active) return;

    _registry->update(t);

    for (Particle* p : _particles)
    {
        p->integrate(t);
    }

}



MuellePracticaSystem::~MuellePracticaSystem()
{

}

void MuellePracticaSystem::setK(int K)
{
    _spring1->setK(K);
    _spring2->setK(K);
}


