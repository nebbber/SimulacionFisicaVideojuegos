#include "BulletSystem.h"
#include <cmath> // para pow

BulletSystem::BulletSystem(Gravity* g, OscillateWind* o)
{
    _oscillate = 0;
    _gravity = g;
    _registry = new ForceRegistry();
    bullets.reserve(100);
}

BulletSystem::~BulletSystem()
{
    for (Particle* p : bullets)
        delete p;
    bullets.clear();

    delete _registry;
}

void BulletSystem::createBullet(Vector3 pos, double velS, Vector3 velR, Vector3 acc, float damping, float massR, PxVec3 dir, Vector4 color)
{
    double energiaR = 0.5 * massR * pow(velR.magnitude(), 2);
    float masaS = energiaR / pow(velR.magnitude(), 2) * 2;

    Vector3 vel(dir * velS);
    Particle* p = new Particle(0.5, pos, vel, acc, damping, masaS, color, 1.0f);
    p->setGeometry();
    bullets.push_back(p);

    // Registramos la gravedad para la bala
    if (_gravity && _gravity->isActive())
        _registry->add(p, _gravity);

    if (_oscillate && _oscillate->isActive())
        _registry->add(p, _oscillate);
}

bool BulletSystem::isEmpty() const
{
    return bullets.empty();
}

void BulletSystem::shot(double t)
{
    for (int i = bullets.size() - 1; i >= 0; --i)
    {
        bullets[i]->integrate(t);

        // si está a una distancia de más de 125 borramos la bala
        if (bullets[i]->getPos().magnitude() > 125.0)
        {
            _registry->removeParticle(bullets[i]);
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
    }

    // Actualizamos fuerzas de todas las balas registradas
    _registry->update(t);
}

std::vector<Particle*> BulletSystem::getBullets() const
{
    return bullets;
}