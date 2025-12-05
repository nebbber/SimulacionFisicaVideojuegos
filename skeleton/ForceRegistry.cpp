#include "ForceRegistry.h"
#include "SolidSystem.h"

void ForceRegistry::add(Particle* p, ForceGenerator* fg) {
    particleToGenerators[p].push_back(fg);
    generatorToParticles[fg].push_back(p);
}

void ForceRegistry::add(PxRigidDynamic* r, ForceGenerator* fg)
{
    rigidToGenerators[r].push_back(fg);
    generatorToRigids[fg].push_back(r);
}
void ForceRegistry::remove(PxRigidDynamic* r, ForceGenerator* fg)
{
    // Quitar fg de la lista de r
    auto& genList = rigidToGenerators[r];
    genList.erase(
        std::remove(genList.begin(), genList.end(), fg),
        genList.end()
    );

    // Quitar r de la lista de fg
    auto& rList = generatorToRigids[fg];
    rList.erase(
        std::remove(rList.begin(), rList.end(), r),
        rList.end()
    );
}
void ForceRegistry::removeRigid(PxRigidDynamic* r)
{
    for (ForceGenerator* fg : rigidToGenerators[r])
    {
        auto& list = generatorToRigids[fg];
        list.erase(std::remove(list.begin(), list.end(), r), list.end());
    }

    rigidToGenerators.erase(r);
}

// Eliminar todas las asociaciones de un generador
void ForceRegistry::removeGenerator(ForceGenerator* fg) {
    if (generatorToParticles.find(fg) != generatorToParticles.end()) {
        for (auto* p : generatorToParticles[fg]) {
            auto& genList = particleToGenerators[p];
            genList.erase(std::remove(genList.begin(), genList.end(), fg), genList.end());
        }
        generatorToParticles.erase(fg);
    }
}

void ForceRegistry::removeParticle(Particle* p)
{
    if (particleToGenerators.find(p) == particleToGenerators.end()) return;
     for (auto* fg : particleToGenerators[p]) {
            auto& parts = generatorToParticles[fg];
            parts.erase(std::remove(parts.begin(), parts.end(), p), parts.end());
        }
        particleToGenerators.erase(p);
    
}


void ForceRegistry::update(float duration) {
    for (auto& pair : particleToGenerators) {
        Particle* p = pair.first;
        std::vector<ForceGenerator*>& generators = pair.second;

        if (!p) continue; // ignorar partículas nulas

        for (auto* fg : generators) {
            if (!fg) continue; // ignorar generadores nulos
            fg->update(duration, p);
        }
    }

    for (auto& pair : rigidToGenerators)
    {
        PxRigidDynamic* r = pair.first;
        for (ForceGenerator* fg : pair.second)
            fg->update(duration, r);
    }
}