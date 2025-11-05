#include "ForceRegistry.h"

void ForceRegistry::add(Particle* p, ForceGenerator* fg) {
    particleToGenerators[p].push_back(fg);
    generatorToParticles[fg].push_back(p);
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
}