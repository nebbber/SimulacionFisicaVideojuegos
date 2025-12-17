#include "muelleMovible.h"
#include "OscillateWind.h"
#include "Gravity.h"
#include "ForceRegistry.h"
#include "SpringForceGenerator.h"
#include "GaussianGen.h"
#include "BreathWater.h"
#include "Whirlwind.h"
muelleMovible::muelleMovible(Gravity* g, Vector3 startPos) : ParticleSystem()
{
    _gravity = g;
    _registry = new ForceRegistry();

    // Partícula principal
    particulaMovible = new Particle(
        700.0, startPos, Vector3(0, 0, 0), Vector3(0, 0, 0),
        0.0f, 1.0f, Vector4(0.8f, 0.3f, 0.54f, 1.0f), 4.0f
    );
    particulaMovible->setGeometry();

    // Partícula del extremo del muelle
    Vector3 p2Pos = startPos + Vector3(0, 40, 0); 
    Vector3 p2Vel(0, 5, 0); 
    p2Muelles = new Particle(
        700.0, p2Pos, p2Vel, Vector3(0, 0, 0),
        0.4f, 1.0f, Vector4(0.4f, 0.1f, 0.23f, 1.0f), 2.0f
    );
    p2Muelles->setGeometry();

    // Añadir partículas al sistema
    _particles.push_back(particulaMovible);
    _particles.push_back(p2Muelles);

    // Cada muelle tiene su propio spring
    _spring2 = new SpringForceGenerator(2, 2);
    _spring2->setParticle(particulaMovible);
    _registry->add(p2Muelles, _spring2);

    // Aplicar gravedad
    _registry->add(p2Muelles, _gravity);

    _whril = new Whirlwind(
        2.0f,                  
        Vector3(0, 0, 0),       
        Vector3(10.0f, 0, 0), 
        1.0f,                    
        0.5f                     
    );
    BreathWaterSys = new BreathWater(nullptr, _whril);

    
    speed = 10.0f;     
    rightLimit = 100.0f;  
    leftLimit = 10.0f;   
}
void muelleMovible::update(double t)
{
    if (particulaMovible &&active) {
        Vector3 pos = particulaMovible->getPos();

        if (pos.x >= rightLimit) {
            // Cambiar dirección a izquierda
            pos.x = rightLimit; // evitar pasar límite
            _isMovingRight = false;
        }
        else if (pos.x <= leftLimit) {
            // Cambiar dirección a derecha
            pos.x = leftLimit; // evitar pasar límite
            _isMovingRight = true;
        }

        // Mover según la dirección actual
        if (_isMovingRight) {
            pos.x += speed * t;
        }
        else {
            pos.x -= speed * t;
        }

        particulaMovible->setPos(pos);

        if (particulaMovible && BreathWaterSys)
        {
            Vector3 pos = particulaMovible->getPos();
            Vector3 fuentePos = pos + Vector3(0, 5, 0); 
            BreathWaterSys->setPosition(fuentePos);
        }

    }
    if (BreathWaterSys) {
        BreathWaterSys->update(t);
    }

    _registry->update(t);

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

muelleMovible::~muelleMovible()
{
    if (BreathWaterSys) {
        delete BreathWaterSys;
        BreathWaterSys = nullptr;
    }

}

void muelleMovible::setPosMovible(Vector3 pos)
{
    particulaMovible->setPos(pos);

    Vector3 p(pos.x, pos.y-3, pos.z);
    p2Muelles->setPos(p);
}

void muelleMovible::setK(int K)
{
    _spring2->setK(K);
}

Vector3 muelleMovible::getPos()
{
    return particulaMovible->getPos();
}

float muelleMovible::getRadius() const 
{
    return particulaMovible->getRadius();
}

void muelleMovible::deactivate()
{
    active = false;

    if (particulaMovible) particulaMovible->hide();
    if (p2Muelles)        p2Muelles->hide();
    if (BreathWaterSys) {
        BreathWaterSys->stopEmission();  
    }
}