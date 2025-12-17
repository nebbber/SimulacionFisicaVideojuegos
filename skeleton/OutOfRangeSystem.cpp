#include "OutOfRangeSystem.h"
#include "WindGenerator.h"
#include "Gravity.h"
#include "ForceRegistry.h"
#include "OscillateWind.h"
#include "UniformGen.h"
//poner la gravedad de parametro y asi la tiene
OutOfRangeSystem::OutOfRangeSystem(Gravity* g, WindGenerator* w, OscillateWind* o) :ParticleSystem()
{
    _gravity = g;
    _wind = w;
    _oscillate = o;
    p = new UniformGen("fueraAlcance");
    _registry = new ForceRegistry();
    _generators.push_back(p);

    Particle* modeloNieve = new Particle(
        7.0, Vector3(0, 0, 0), Vector3(0, 0, 0),
        Vector3(0, 0, 0), 0.4f, 40.0f, Vector4(0.86, 0.07, 0.23, 1), 1.0f 
    );

    p->setModelo(modeloNieve);
    p->setNumParticles(100);
    p->setDurMedia(0.4);
    p->setPosMedia(Vector3(0, 50, -80));
    p->setVelMedia(Vector3(0, -5, 0));
    p->setDesP(Vector3(200, 50, 200));
    p->setDesV(Vector3(3, 2, 3));
    p->setProbGen(0.3);

}

void OutOfRangeSystem::update(double t)
{
    // no esta activo no añado particulas 
    if (active)
    {
        // Generar nuevas partículas
        for (ParticleGen* gen : _generators)
        {
            auto generatedParticles = gen->generateP();
            std::string groupName = gen->getName();


            for (Particle* p : generatedParticles)
            {
                p->setShape(2);
                p->setGeometry();
                _particles.push_back(p);


                if (_oscillate && _oscillate->isActive())
                    _registry->add(p, _oscillate);
                else if (_oscillate && !_oscillate->isActive())
                {
                    _registry->removeGenerator(_oscillate);
                }
                if (_gravity && _gravity->isActive())
                    _registry->add(p, _gravity);
                else if (_gravity && !_gravity->isActive())
                {
                    _registry->removeGenerator(_gravity);
                }

                if (_wind && _wind->isActive())
                    _registry->add(p, _wind);
                else if (_wind && !_wind->isActive())
                {
                    _registry->removeGenerator(_wind);
                }

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



OutOfRangeSystem::~OutOfRangeSystem()
{

}


