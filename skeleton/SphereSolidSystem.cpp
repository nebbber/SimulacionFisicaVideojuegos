#include "SphereSolidSystem.h"
#include <random>
#include <algorithm> 
#include "ForceRegistry.h"

SphereSolidSystem::SphereSolidSystem(PxPhysics* p, PxScene* s, Gravity* g, OscillateWind* w, PxVec3 pos) :SolidSystem()
{
    _gravity = g;
     _oscillate = w;
    defaultMat = p->createMaterial(0.0f, 1.5f, 0.6f);
    scene = s;

    sphere = new GaussianSolidGen(p, s, defaultMat, 1);
    _registry = new ForceRegistry();
    sphere->setShapeType(SolidShapeType::SPHERE);
    sphere->setSize(1);

    sphere->setProbGen(0.4);
    sphere->setPosMedia(pos);
    sphere->setDesvPos(PxVec3(10, 1, 10));
    sphere->setVelMedia(PxVec3(0, 0, 0));
    sphere->setDesvVel(PxVec3(1, 1, 1));
    sphere->setMassMedia(3.0f);


}
Vector4 SphereSolidSystem::randomColor()
{
    static std::mt19937 rng(std::random_device{}());

    static const std::vector<Vector4> colors = {
        {1.0f, 0.0f, 0.0f, 1.0f},  // rojo
        {0.0f, 1.0f, 0.0f, 1.0f},  // verde
        {0.0f, 0.0f, 1.0f, 1.0f},  // azul
        {1.0f, 1.0f, 0.0f, 1.0f},  // amarillo
        {1.0f, 0.5f, 0.0f, 1.0f},  // naranja
        {1.0f, 0.0f, 1.0f, 1.0f},  // rosa
        {0.0f, 1.0f, 1.0f, 1.0f},  // cian
        {0.5f, 0.0f, 1.0f, 1.0f}   // violeta
    };

    std::uniform_int_distribution<int> dist(0, colors.size() - 1);
    return colors[dist(rng)];
}
void SphereSolidSystem::update(double t)
{
   // if (!active)
    //    return;

    auto newBodies = sphere->generateRigidBodies();

    for (auto body : newBodies)
    {

        if (_gravity && _gravity->isActive())
            _registry->add(body, _gravity);


        if (_oscillate && _oscillate->isActive())
            _registry->add(body, _oscillate);
        else if (_oscillate && !_oscillate->isActive())
        {
            _registry->removeGenerator(_oscillate);
        }

        bodies.push_back(body);

        // Crear y registrar RenderItem
        PxShape* shape = CreateShape(
            PxSphereGeometry(sphere->getSize()),
            defaultMat
        );

        RenderItem* item = new RenderItem(shape, body, randomColor());
        renderItems.push_back(item);
    }

    _registry->update(t);

    removeDeadBodies();
}


void SphereSolidSystem::removeDeadBodies()
{
    auto it = bodies.begin();

    while (it != bodies.end())
    {
        PxRigidActor* actor = *it;

        bool shouldDie = (actor->getGlobalPose().p.y < -50.0f);

        if (shouldDie)
        {

            for (auto& item : renderItems)
            {
                if (item->actor == actor)
                {
                    DeregisterRenderItem(item);
                    item->actor = nullptr;
                }
            }

            if (_registry && actor->is<PxRigidDynamic>())
            {
                PxRigidDynamic* dyn = static_cast<PxRigidDynamic*>(actor);
                _registry->removeRigid(dyn);
            }

            if (scene)
                scene->removeActor(*actor);

            actor->release();

            it = bodies.erase(it);
        }
        else
        {
            ++it;
        }
    }
    renderItems.erase(
        std::remove_if(renderItems.begin(), renderItems.end(),
            [](RenderItem* item) { return item->actor == nullptr; }),
        renderItems.end()
    );
}
SphereSolidSystem::~SphereSolidSystem()
{
}