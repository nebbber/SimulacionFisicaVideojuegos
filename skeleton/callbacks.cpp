#include "callbacks.hpp"
#include "SceneManager.h"

extern SceneManager* gSceneManager; // declarado en main.cpp

physx::PxFilterFlags contactReportFilterShader(
    physx::PxFilterObjectAttributes attributes0, physx::PxFilterData filterData0,
    physx::PxFilterObjectAttributes attributes1, physx::PxFilterData filterData1,
    physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize)
{
    PX_UNUSED(attributes0);
    PX_UNUSED(attributes1);
    PX_UNUSED(filterData0);
    PX_UNUSED(filterData1);
    PX_UNUSED(constantBlockSize);
    PX_UNUSED(constantBlock);

    pairFlags = physx::PxPairFlag::eSOLVE_CONTACT
        | physx::PxPairFlag::eDETECT_DISCRETE_CONTACT
        | physx::PxPairFlag::eNOTIFY_TOUCH_FOUND
        | physx::PxPairFlag::eNOTIFY_TOUCH_PERSISTS
        | physx::PxPairFlag::eNOTIFY_CONTACT_POINTS;

    return physx::PxFilterFlag::eDEFAULT;
}

void ContactReportCallback::onContact(
    const physx::PxContactPairHeader& pairHeader,
    const physx::PxContactPair* pairs,
    physx::PxU32 nbPairs)
{
    PX_UNUSED(pairs);
    PX_UNUSED(nbPairs);

    if (gSceneManager)
        gSceneManager->onCollision(pairHeader.actors[0], pairHeader.actors[1]);
}