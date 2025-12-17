#include "BreathWater.h"
#include "GaussianGen.h"
#include "ForceRegistry.h"
#include "Gravity.h"
#include "Whirlwind.h"
BreathWater::BreathWater(Gravity* g, Whirlwind* w)
{
    _gravity = g;
    _whril = w;
    p = new GaussianGen("aguaRespirar");
    _generators.push_back(p);

    _registry = new ForceRegistry();

    
    Particle* modelo = new Particle(700.0, Vector3(0, 0, 0), Vector3(0, 0, 0),
        Vector3(0, 0, 0), 0.4f, 20.0f, Vector4(0, 0, 1, 1), 1.0f);
    p->setModelo(modelo);
  
    p->setNumParticles(1);
    p->setDurMedia(0.4);
    p->setPosMedia(Vector3(25.0f, 0.0f, 0.0f));
    p->setVelMedia(Vector3(0.0f, 40.0f, 0.0f)); // velocidad de subida más fuerte
    p->setDesV(Vector3(5.0f, 5.0f, 5.0f));      // variación
    p->setDesP(Vector3(1, 0, 1));
    p->setProbGen(0.05);
    active = true;
}
void BreathWater::stopEmission()
{
    emitting = false;
}
void BreathWater::update(double t)
{
    
    // no esta activo no añado particulas 
    if (emitting&&active)
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

BreathWater::~BreathWater()
{
}
void BreathWater::setPosition(const Vector3& pos)
{
    if (p)
    {
        p->setPosMedia(pos);
    }
}