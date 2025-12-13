
#include "CubeSolidSystem.h"
#include "ForceRegistry.h"
#include <random>
CubeSolidSystem::CubeSolidSystem(PxPhysics* p, PxScene* s, Gravity* g, OscillateWind* w, PxVec3 pos):SolidSystem()
{
    _gravity = g;
   // _oscillate = w;
     defaultMat = p->createMaterial(0.5f, 0.5f, 0.6f);
     scene = s;

    cube = new GaussianSolidGen(p, s, defaultMat, 1); 
    _registry = new ForceRegistry();
    cube->setShapeType(SolidShapeType::BOX); //tambien hay que cambair en el update el tipo
    cube->setSize(2);

    cube->setProbGen(0.04);
    cube->setPosMedia(pos); 
    cube->setDesvPos(PxVec3(10, 1, 10));
    cube->setVelMedia(PxVec3(0, 0, 0));
    cube->setDesvVel(PxVec3(1, 1, 1));

   
}

Vector4 CubeSolidSystem::randomColor()
{
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    return Vector4(
        dist(rng),
        dist(rng), 
        dist(rng), 
        1.0f        
    );
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

        if (_whril && _whril->isActive())
            _registry->add(body, _whril);

        if (_oscillate && _oscillate->isActive())
            _registry->add(body, _oscillate);

       
        bodies.push_back(body);

        // Crear y registrar RenderItem
        PxShape* shape = CreateShape(
            PxBoxGeometry(cube->getSize(), cube->getSize(), cube->getSize()),
            defaultMat
        );

        RenderItem* item = new RenderItem(shape, body, randomColor());
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

        bool shouldDie = (actor->getGlobalPose().p.y < -10.0f);

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
CubeSolidSystem::~CubeSolidSystem()
{
}