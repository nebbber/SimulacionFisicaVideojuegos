#include <PxPhysicsAPI.h>
#include <vector>
#include "Gravity.h"
#include "WindGenerator.h"
#include "SpringForceGenerator.h"
#include "ForceRegistry.h"
using namespace physx;
class SolidSystem {
public:
    
    std::vector<PxRigidActor*> bodies; 
    ForceRegistry registry;

    Gravity* gravity;
    WindGenerator* wind;
    SpringForceGenerator* spring;

    SolidSystem();
    ~SolidSystem();

    void addRigidBody(PxRigidActor* rb);
    void update(float dt);
};