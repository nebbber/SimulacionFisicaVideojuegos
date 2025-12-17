#include "BackgroundWaterSystem.h"
#include "OscillateWind.h"
#include "Gravity.h"
#include "ForceRegistry.h"
#include "GaussianGen.h"
//poner la gravedad de parametro y asi la tiene
BackgroundWaterSystem::BackgroundWaterSystem(Gravity* g, WindGenerator* w, OscillateWind* o):ParticleSystem()
{
    _gravity = g;
    _oscillate = o;
    _wind = w;
    p = new GaussianGen("aguaFondo");
    _generators.push_back(p);
 
    // Crear el modelo de fuego
    Particle* modelo = new Particle(
        700.0,
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        0.4f,
        20.0f,
        Vector4(0.0f, 1.0f, 1.0f, 1.0f),
        0.4f
        
    );
    _registry = new ForceRegistry();
    // Configurar el sistema de partículas
    p->setModelo(modelo);
    p->setNumParticles(10);
    p->setDurMedia(5.0);
    p->setPosMedia(Vector3(30.0f, 0.0f, -80.0f));
    p->setVelMedia(Vector3(10.0f, 10.0f, 10.0f));
    p->setDesP(Vector3(100.0f, 0, 100.0f));
    p->setDesV(Vector3(20, 20, 20));
    p->setProbGen(0.6);

}

void BackgroundWaterSystem::update(double t)
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
                p->setShape(1);
                p->setGeometry();
                _particles.push_back(p);

                if (_oscillate && _oscillate->isActive())
                    _registry->add(p, _oscillate);
                else if (_oscillate && !_oscillate->isActive())
                {
                    _registry->removeGenerator(_oscillate);
                }
                if (_gravity&&_gravity->isActive())
                    _registry->add(p, _gravity);
                else if (_gravity && !_gravity->isActive())
                {
                    _registry->removeGenerator( _gravity);
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



BackgroundWaterSystem::~BackgroundWaterSystem()
{

}


