#include "CubeSolidSystem.h"
#include "Gravity.h"
#include "ForceRegistry.h"
#include "GaussianSolidGen.h"

CubeSolidSystem::CubeSolidSystem(PxPhysics* p, PxScene* s, Gravity* g):SolidSystem()
{
    _gravity = g;

     defaultMat = p->createMaterial(0.5f, 0.5f, 0.6f);

    cube = new GaussianSolidGen(p, s, defaultMat, 1); // 20 cubos
    _registry = new ForceRegistry();

  
    cube->setPosMedia(PxVec3(50, 205, -80));
    cube->setDesvPos(PxVec3(1, 1, 1));
    cube->setVelMedia(PxVec3(0, 0, 0));
    cube->setDesvVel(PxVec3(1, 1, 1));

   
}
void CubeSolidSystem::update(double t)
{
    if (!active) return;

    
        auto newBodies = cube->generateRigidBodies();
        for (auto body : newBodies)
        {
            if (_gravity && _gravity->isActive())
                _registry->add(body, _gravity);

            bodies.push_back(body);

            PxShape* shape = CreateShape(PxBoxGeometry(5, 5, 5), defaultMat);
            RenderItem* item = new RenderItem(shape, body, Vector4(1, 0, 0, 1));
            RegisterRenderItem(item);
        }
      
    

    _registry->update(t);
}

CubeSolidSystem::~CubeSolidSystem()
{
}
