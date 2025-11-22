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
  
    ptoAnclajeCubo = new Particle(700.0, Vector3(40, 40, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.4f, 20.0f, Vector4(1.0f, 0.0f, 0.5f, 1.0f), 1.0f);
    ptoAnclajeCubo->setShape(2);//que sea cubo
    ptoAnclajeCubo->setGeometry();
  

    p1Muelles = new Particle(700.0, Vector3(40, 10, 0), Vector3(20.0f, 0, 0), Vector3(0, 0, 0), 0.4f, 1.0f, Vector4(1.0f, 0.0f, 0.5f, 1.0f), 1.0f);
    p1Muelles->setGeometry();
    p2Muelles = new Particle(700.0, Vector3(40, 37, 0), Vector3(20.0f, 0, 0), Vector3(0, 0, 0), 0.4f, 1.0f, Vector4(1.0f, 0.0f, 0.5f, 1.0f), 1.0f);
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

}

void MuellePracticaSystem::update(double t)
{
    // no esta activo no añado particulas 
   if (active)
    {
        for (Particle* p : _particles) {
            
             if (_spring1 && !_spring1->isActive())
            {
                _registry->removeGenerator(_spring1);
            }
             else if (_spring1 && _spring1->isActive())
             {
                 _registry->add(p, _spring1);
                
             }
     
             if (_gravity && !_gravity->isActive())
            {
                _registry->removeGenerator(_gravity);
            }
             else if (_gravity && _gravity->isActive())
             {
                 _registry->add(p, _gravity);
             }

         
             if (_spring2 && !_spring2->isActive())
            {
                _registry->removeGenerator(_spring2);
            }
             else if (_spring2 && _spring2->isActive())
             {
                 _registry->add(p, _spring2);
             }

       
    }   }
   
    _registry->update(t);

    // integrar e ignorar las particulas muertas por si dan error
    auto it = _particles.begin();
    while (it != _particles.end()) {
        Particle* p = *it;
        if (!p->isAlive()) {
            _registry->removeParticle(p);
            delete p;
            it = _particles.erase(it);
        }
        else {
            p->integrate(t);
            ++it;
        }
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


