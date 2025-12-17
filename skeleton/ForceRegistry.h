#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "Particle.h"
#include "ForceGenerator.h"

class ForceRegistry {
private:
    
    std::unordered_map<Particle*, std::vector<ForceGenerator*>> particleToGenerators;

    std::unordered_map<ForceGenerator*, std::vector<Particle*>> generatorToParticles;

    std::unordered_map<PxRigidDynamic*, std::vector<ForceGenerator*>> rigidToGenerators;

    std::unordered_map<ForceGenerator*, std::vector<PxRigidDynamic*>> generatorToRigids;

public:
    
    void add(Particle* p, ForceGenerator* fg);

    //para solidos
    void add(PxRigidDynamic* r, ForceGenerator* fg);
    void remove(PxRigidDynamic* r, ForceGenerator* fg);
    void removeRigid(PxRigidDynamic* r);

    // para particulas
    void remove(Particle* p, ForceGenerator* fg);
    void removeGenerator(ForceGenerator* fg);
    void removeParticle(Particle* p);

    // Actualizar todas las fuerzas
    void update(float duration);
};