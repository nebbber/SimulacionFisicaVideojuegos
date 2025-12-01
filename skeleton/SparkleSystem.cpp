#include "SparkleSystem.h"
#include "OscillateWind.h"
#include "Gravity.h"
#include "ForceRegistry.h"
#include "GaussianGen.h"
//poner la gravedad de parametro y asi la tiene
SparkleSystem::SparkleSystem(Gravity* g, WindGenerator* w, OscillateWind* o):ParticleSystem()
{
    _gravity = g;
    _oscillate = o;
    _wind = w;
    spark = new GaussianGen("spark");
    _generators.push_back(spark);
 
    // Crear el modelo de fuego
    Particle* modeloFuego = new Particle(
        7.0,
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        Vector3(0, 0, 0),
        0.4f,
        20.0f,
        Vector4(1.0f, 0.0f, 0.5f, 1.0f),
        1.0f
        
    );
    _registry = new ForceRegistry();
    // Configurar el sistema de partículas
    spark->setModelo(modeloFuego);
    spark->setNumParticles(20);
    spark->setDurMedia(1.0);
    spark->setPosMedia(Vector3(30.0f, 20.0f, -80.0f));
    spark->setVelMedia(Vector3(10.0f, 10.0f, 10.0f));
    spark->setDesP(Vector3(0.4f, 0, 0.4f));
    spark->setDesV(Vector3(20, 20, 20));
    spark->setProbGen(0.2);

}

void SparkleSystem::update(double t)
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



SparkleSystem::~SparkleSystem()
{

}


