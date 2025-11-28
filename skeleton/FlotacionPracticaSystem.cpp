#include "FlotacionPracticaSystem.h"
#include "Gravity.h"
#include "FloatForce.h"
#include "ForceRegistry.h"
FlotacionPracticaSystem::FlotacionPracticaSystem(Gravity* g, FloatForce* f)
{
    _gravity = g;
    _float = f;

    _registry = new ForceRegistry();

    objeto = new Particle(700.0, Vector3(40, 20, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.3f, 500.0f, Vector4(0.0f, 1.0f, 0.0f, 1.0f), 1.0f);
 
    objeto->setShape(2);//que sea cubo
    objeto->setGeometry();


    agua = new Particle(700.0, Vector3(40,0, 0), Vector3(0.0f, 0, 0), Vector3(0, 0, 0), 0.4f, 1.0f, Vector4(0.0f, 0.0f, 1.5f, 1.0f), 1.0f);
    agua->setH(1.0f);
    agua->setP(10.0f);
    agua->setW(10.0f); 

    agua->setShape(2);//que sea cubo
    agua->setGeometry();
   
    _float->setLiquidParticle(agua);

    _particles.push_back(objeto);
    _particles.push_back(agua);

    _registry->add(objeto, _gravity); //la que voy a mover
    _registry->add(objeto, _float);
  
}

void FlotacionPracticaSystem::setMasa(float m)
{
    objeto->setMasa(m);

}


void FlotacionPracticaSystem::update(double t)
{

   if (active)
    {
        for (Particle* p : _particles) {

            if (_float && !_float->isActive())
            {
                _registry->removeGenerator(_float);
            }
            else if (_float && _float->isActive())
            {
                _registry->add(p, _float);

            }

            if (_gravity && !_gravity->isActive())
            {
                _registry->removeGenerator(_gravity);
            }
            else if (_gravity && _gravity->isActive())
            {
                _registry->add(p, _gravity);
            }




        }
    }
    
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

FlotacionPracticaSystem::~FlotacionPracticaSystem()
{
}

