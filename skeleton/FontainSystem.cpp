#include "FontainSystem.h"
#include "GaussianGen.h"
#include "ForceRegistry.h"
#include "Gravity.h"
#include "Whirlwind.h"
FontainSystem::FontainSystem(Gravity* g, Whirlwind* w)
{
    _gravity = g;
    _whril = w;
    fuente = new GaussianGen("fuente");
    _generators.push_back(fuente);

    _registry = new ForceRegistry();

    // Modelo fuente
    Particle* modeloFuente = new Particle(700.0, Vector3(0, 0, 0), Vector3(0, 0, 0),
        Vector3(0, 0, 0), 0.4f, 20.0f, Vector4(0.07, 0.42, 0.64, 1), 1.0f);
    fuente->setModelo(modeloFuente);
  
    fuente->setNumParticles(1);
    fuente->setDurMedia(0.2);
    fuente->setPosMedia(Vector3(25.0f, 0.0f, 0.0f));
    fuente->setVelMedia(Vector3(0.0f, 40.0f, 0.0f)); // velocidad de subida más fuerte
    fuente->setDesV(Vector3(5.0f, 5.0f, 5.0f));      // variación
    fuente->setDesP(Vector3(1, 0, 1));
    fuente->setProbGen(0.01);
    active = true;
}

void FontainSystem::update(double t)
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


                if (_gravity && _gravity->isActive())
                    _registry->add(p, _gravity);
                else if (_gravity && !_gravity->isActive())
                {
                    _registry->removeGenerator(_gravity);
                }

                if (_whril && _whril->isActive())
                    _registry->add(p, _whril);
                else if (_whril && !_whril->isActive())
                {
                    _registry->removeGenerator(_whril);
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

FontainSystem::~FontainSystem()
{
}
void FontainSystem::setPosition(const Vector3& pos)
{
    if (fuente)
    {
        fuente->setPosMedia(pos);
    }
}