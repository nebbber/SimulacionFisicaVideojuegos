
#include "CubeSolidSystem.h"
#include "ForceRegistry.h"
#include <random>
CubeSolidSystem::CubeSolidSystem(PxPhysics* p, PxScene* s, Gravity* g, OscillateWind* w, PxVec3 pos):SolidSystem()
{
    _gravity = g;
    //_oscillate = w;
     defaultMat = p->createMaterial(0.5f, 0.5f, 0.6f);
     scene = s;

    cube = new GaussianSolidGen(p, s, defaultMat, 1); 
    _registry = new ForceRegistry();
    cube->setShapeType(SolidShapeType::BOX); //tambien hay que cambiar en el update el tipo
    cube->setSize(2);

    cube->setProbGen(0.04);
    cube->setPosMedia(pos); 
    cube->setDesvPos(PxVec3(10, 1, 10));
    cube->setVelMedia(PxVec3(0, 0, 0));
    cube->setDesvVel(PxVec3(1, 1, 1));

   
}

void CubeSolidSystem::update(double t)
{
    if (!active)
        return;

    auto newBodies = cube->generateRigidBodies();

    for (auto body : newBodies)
    {
        
        if (_gravity && _gravity->isActive())
            _registry->add(body, _gravity);


        if (_oscillate && _oscillate->isActive())
            _registry->add(body, _oscillate);

       
        bodies.push_back(body);

        // Crear y registrar RenderItem
        PxShape* shape = CreateShape(
            PxBoxGeometry(cube->getSize(), cube->getSize(), cube->getSize()),
            defaultMat
        );

        RenderItem* item = new RenderItem(shape, body, Vector4 (1.0f, 1.0f, 0.0f, 1.0f));
        renderItems.push_back(item);     
    }

    _registry->update(t);

    removeDeadBodies();
}


void CubeSolidSystem::removeDeadBodies()
{
    auto it = bodies.begin();
    while (it != bodies.end())
    {
        PxRigidActor* actor = *it;

        if (!actor)
        {
            it = bodies.erase(it);
            continue;
        }

        bool shouldDie = (actor->getGlobalPose().p.y < -10.0f);
        if (shouldDie)
        {
            // Desregistrar RenderItems
            for (auto& item : renderItems)
            {
                if (item->actor == actor)
                {
                    DeregisterRenderItem(item);
                    item->actor = nullptr;
                }
            }

            // Remover de _registry si es dinámico
            if (_registry && actor->is<PxRigidDynamic>())
                _registry->removeRigid(static_cast<PxRigidDynamic*>(actor));

            // Remover de la escena
            if (scene)
                scene->removeActor(*actor);

            // Liberar actor
            actor->release();

            // Marcar como nullptr para que no se vuelva a liberar
            *it = nullptr;
            it = bodies.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // Limpiar renderItems nulos
    renderItems.erase(
        std::remove_if(renderItems.begin(), renderItems.end(),
            [](RenderItem* item) { return item->actor == nullptr; }),
        renderItems.end()
    );
}
CubeSolidSystem::~CubeSolidSystem()
{
    for (PxRigidActor* actor : bodies)
    {
        if (!actor) continue;

        if (_registry && actor->is<PxRigidDynamic>())
            _registry->removeRigid(static_cast<PxRigidDynamic*>(actor));

        if (scene!=nullptr)
            scene->removeActor(*actor);

        actor->release();
    }
    bodies.clear();

    for (RenderItem* item : renderItems)
    {
        if (item)
        {
            if (item->shape)
                item->shape->release();
            delete item;
        }
    }
    renderItems.clear();

    delete cube;
    delete _registry;

}